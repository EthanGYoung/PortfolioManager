//
// Created by Ethan Young on 1/1/18.
//

#include "Algorithm.h"
#include <glpk.h>
#include <iostream>

Algorithm::Algorithm(int interval, Fund *fundEx, vector<string> *factorNames) {
    testInterval = interval;
    fund = fundEx;
    faName = factorNames;
    stockList = fund->getStockList();
}

Algorithm::~Algorithm() {

}


//Dates are chosen by the backtest will predict the Date passed in
//Date: The date to be predicted
//Fund: The fund that is used to predict the data
//Stock:
//Model
//Objective: min sum(currDay over all days in interval) error(day)
//Constraint: actual(currDay) = A * Factor1(prevDay) + B * Factor2(prevDay) + C * Factor3(prevDay) + error(currDay)
//Note: Have a constraint for each day in the interval

//Get coefficients A, B, C, ..
//Use to predict the current day of the date passed in
//Return the predicted value or whether increase or decrease
double Algorithm::predictDate(tm *Date, Stock *st) {
    cout << "predictDate in algorithm" << endl;

    glp_prob *lp; //LP instance

    //Size of the arrays is number factors + 2 * interval for error terms and then one for each day
    int size = ((int) faName->size() + testInterval * 2) * testInterval + 1;

    //ia is constraint index, ja is variable index, ar is coeff for everything
    int ia[size], ja[size];
    double ar[size], z, results[size]; //Results are the variable values

    //Problem objective which is empty (Zero rows or columns)
    lp = glp_create_prob();

    //Sets the name of the lp prob
    glp_set_prob_name(lp, "Regression");

    //Sets direction of LP (Default is min)
    glp_set_obj_dir(lp, GLP_MIN);

    //Rows are the constraints (Constraint for each date)
    glp_add_rows(lp, testInterval);

    //This is the index value into the date list for the starting date
    int indexVal = getDateIndex(Date, st, fund) - testInterval;

    int i = 1; //Counter for the rows

    vector<tm *> *dates = fund->getDateList();
    vector<tm *>::iterator it;
    vector<string>::iterator itr;


    //Gets actuals for the bounds and goes backwards to the correct date
    cout << "Predicting Date: " << st->convertDate(Date) << endl;
    for (it = dates->begin() + indexVal; i < testInterval + 1; it++) {
        double actual = st->getFactorValue("OpenPrice", *it);

        //Equality constraint
        glp_set_row_bnds(lp, i, GLP_FX, actual, actual);
        i++;
    }

    //Number variables in factor size + numConstraints*2 (2 errors for each constraint)
    int numVars = (int) (faName->size() + testInterval * 2);

    //Creates the variables
    glp_add_cols(lp, numVars);

    //Creates a free variable for every factor and 2 non neg for every constraint
    for (int j = 1; j < numVars + 1; j++) {
        if (j < (int) (faName->size() + 1)) {
            glp_set_col_bnds(lp, j, GLP_FR, 0.0, 0.0);
        } else {
            glp_set_col_bnds(lp, j, GLP_LO, 0.0, 0.0);
            glp_set_obj_coef(lp, j, 1.0); //Sets objective coeff
        }
    }

    int j = 1;
    int varNum = 0;

    //Loop through variables that are factors
    for (itr = faName->begin(); itr != faName->end(); itr++) {
        i = 1;
        varNum++;

        //Loops through constraints and sets coefficients (-1 because using prevday's data to predict next day)
        for (it = dates->begin() + indexVal - 1; i < testInterval + 1; it++) {
            ia[j] = i; //Loops through constraints
            ja[j] = varNum; //Loops through variables
            ar[j] = st->getFactorValue(*itr, *it);
            j++;
            i++;
        }
    }

    //Creates positive and negative error term for each constraint
    for (int n = 1; n < testInterval + 1; n++) {
        //Loops through all possible error values
        for (int k = (int) faName->size() + 1; k < 2 * testInterval + 1 + (int) faName->size(); k++) {
            ia[j] = n; //Loops through constraints
            ja[j] = k; //Loops over error variables

            //Sets coefficients for error vars
            if (k == 2 * (n - 1) + (int) faName->size() + 1) {
                ar[j] = 1.0;
            } else if (k == 2 * (n - 1) + (int) faName->size() + 2) {
                ar[j] = -1.0;
            } else {
                ar[j] = 0;
            }

            j++;
        }
    }

    //Prints out matrix for testing
    //cout << "Stock: " << st->getName() << " Passed in Date: " << st->convertDate(Date) << endl;
    //for (int k = 1; k < size; k++) {
    //   cout << "k = " << k << " IA = " << ia[k] << " JA = " << ja[k] << " AR = " << ar[k] << endl;
    //}

    //Load matrix into program
    glp_load_matrix(lp, size - 1, ia, ja, ar);

    glp_simplex(lp, NULL);

    z = glp_get_obj_val(lp);

    printf("\nz: %f\n", z);

    for (int h = 1; h < (int) faName->size() + 1; h++) {
        cout << "Var" << h << ": " << glp_get_col_prim(lp, h) << " ";
        results[h] = glp_get_col_prim(lp, h);
    }
    cout << endl;
    for (int h = (int) faName->size() + 1; h < (int) faName->size() + 2 * testInterval + 1; h++) {
        cout << "Error" << h << ": " << glp_get_col_prim(lp, h) << " ";
        results[h] = glp_get_col_prim(lp, h);
    }

    glp_delete_prob(lp);

    return getPrediction(results, faName, st, getDateIndex(Date, st, fund), dates);

}

int Algorithm::getDateIndex(tm *Date, Stock *st, Fund *fund) {
    int date = st->convertDate(Date);
    int index = 0;


    vector<tm *> *dates = fund->getDateList();

    vector<tm *>::iterator it;
    for (it = dates->begin(); it != dates->end(); it++) {
        //Checks for matching date and returns the index to it
        if (st->convertDate(*it) == date) {
            return index;
        } else {
            index++;
        }
    }

    //If the date doesn't exist
    return dates->size();;
}

double Algorithm::getPrediction(double result[], vector<string> *faName, Stock *stk, int index, vector<tm *> *dates) {
    double prediction; //The predicted value for the date passed in
    vector<tm *>::iterator date;
    date = dates->begin() + index;

    //cout << "Getting Prediction for date: " << stk->convertDate(*it) << endl;
    //cout << "Using dates from: " << stk->convertDate(*(it - 1)) << endl;

    //Loops through each variable and calculates with prediction date data
    for (int i = 1; i < (int) faName->size() + 1; i++) {
        prediction = prediction + stk->getFactorValue(faName->operator[](i - 1), *(date - 1)) * result[i];
    }

    return prediction;
}


//Model: Used to determine which stocks to buy based on the above algorithm
//scalars b       Total Money     /1000/
//S       Total Stocks    /120/
//N       Number Bought   /10/
//U       Upper percent   /0.25/
//L       Lower percent   /0.05/;

//binary variables
//Y(i)    Buy Decision      //Whether to buy stock i (1 var for each stock)
//Z       Enough Stocks     //1 var total
//;

//nonnegative variables
//X(i)    Money Spent on stock i    //One var for each stock
//;

//variable
//K       Objective                 //Not needed
//Profit  Profit                    //Not needed (Can calculate after)
//;
//Total vars: 2 * numSt + 1
//OBJ      Maximize flow on arcs with high percent model fit,
//eq1      Lower bound on stocks bought,
//eq2      Upper bound on stocks bought,
//eq3      Have to purchase more than N stocks,
//eq4      Detect if less than N stocks can be bought,
//eq5      Upper bound on amount purchased,
//eq6      Calculate total profit,
//eq7      Can't buy a stock if it isn't supposed to increase;

//OBJ..           K =E= sum(i, p(i) * X(i));
//eq1(i)..        a(i) * Y(i) * b * L - X(i) =L= 0;                 numSt eqs            //Lower bound on stocks bought
//eq2(i)..        a(i) * Y(i) * b * U - X(i)=G= 0;                 numSt eqs            //Upper bound on stocks bought
//eq3..           sum(i, Y(i)) - N * Z=G= 0;                       1 eq            //Have to purchase more than N stocks
//eq4..           sum(i, a(i)) - (S - N + 1) * Z - (N - 1) =L= 0;     1 eq            //Detect if less than N stocks can be bought
//eq5..           sum(i, X(i)) - b =L= 0;                           1 eq            //Upper bound on amount purchased
//eq6..           Profit =E= sum(i, X(i) * actuals(i));         Not Needed  //Calculate total profit
//eq7(i)..        Y(i) - a(i) =L= 0;                                NumSt eqs            //Can't buy a stock if it isn't supposed to increase
//Total:    3*numSt + 3
//model stockTrade /all/;
//solve stockTrade using MIP maximizing K;

//Vars: 2*numSt + 1
//Constraints: 3*numSt + 3
double* Algorithm::selectStockDistribution(map<string, double> *percentCorrect, map<string, double> *increase) {
    //Initialize in algorithm when ready
    int totalBudget = 1000;
    int numDiffPurchased = 15;
    double upperPercentLimit = .25;
    double lowerPercentLimit = .05;


    cout << "selectStockDistribution in algorithm" << endl;

    glp_prob *mip; //MIP instance

    //Size of the arrays is number vars (#stocks + 1) * each constraint (3*stocks + 3) + 1 because start at index 1
    int size = (2 * (int) stockList->size() + 1) * (3 * (int) stockList->size() + 2) + 1;


    //ia is constraint index, ja is variable index, ar is coeff for everything (Made pointers because stack overflow)
    int *ia = new int[size];
    int *ja = new int[size];
    double *ar = new double[size];
    double z;
    double *results = new double[size]; //Results are the variable values

    //Problem objective which is empty (Zero rows or columns)
    mip = glp_create_prob();

    //Sets the name of the lp prob
    glp_set_prob_name(mip, "Distribution");

    //Sets direction of LP (Default is min)
    glp_set_obj_dir(mip, GLP_MAX);

    //Rows are the constraints (Constraint for each date)
    glp_add_rows(mip, 3 * (int) stockList->size() + 2);

    //eq1(i)..        a(i) * Y(i) * b * L - X(i) =L= 0;  numSt eqs            //Lower bound on stocks bought
    map<string, Stock>::iterator stock;
    map<string, double>::iterator inc;

    cout << "Printing increase" << endl;

    int i = 1;

    //Sets less than 0 for all stock constraints for eq1
    //eq1(i)..        a(i) * Y(i) * b * L - X(i) =L= 0;                 numSt eqs            //Lower bound on stocks bought
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        glp_set_row_bnds(mip, i, GLP_UP, 0, 0);
        i++;
    }
    //eq2(i)..        a(i) * Y(i) * b * U - X(i)=G= 0;                 numSt eqs            //Upper bound on stocks bought
    //Sets greater than 0 for all stock constraints (Doesn't reset the i)
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        glp_set_row_bnds(mip, i, GLP_LO, 0, 0);
        i++;
    }
    //eq3..           sum(i, Y(i))=G= N;                       1 eq            //Have to purchase more than N stocks
    glp_set_row_bnds(mip, i, GLP_LO, numDiffPurchased, numDiffPurchased);
    i++;
    //eq4..           sum(i, a(i)) - (S - N + 1) * Z - (N - 1) =L= 0;     1 eq            //Detect if less than N stocks can be bought
    //ADD LATER IF NEEDED JUST AN INDICATOR
    //glp_set_row_bnds(mip, i, GLP_UP, numDiffPurchased - 1, numDiffPurchased - 1);
    //i++;
    //eq5..           sum(i, X(i)) - b =L= 0;                           1 eq            //Upper bound on amount purchased
    glp_set_row_bnds(mip, i, GLP_UP, totalBudget, totalBudget);
    i++;

    //eq7(i)..        Y(i) - a(i) =L= 0;                                NumSt eqs            //Can't buy a stock if it isn't supposed to increase
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        glp_set_row_bnds(mip, i, GLP_UP, (increase->find(stock->second.getName())->second),
                         (increase->find(stock->second.getName())->second));
        i++;
    }

    int numVars = 2 * (int) stockList->size() + 1;

    //Creates the variables (2*numSt + 1)
    glp_add_cols(mip, numVars);

    int m = 1;

    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        //Sets the X(i) as nonneg and have obj coeff of their percentages
        glp_set_col_bnds(mip, m, GLP_LO, 0, 0);
        glp_set_obj_coef(mip, m, percentCorrect->find(stock->second.getName())->second);

        //Sets the Y(i) as binary and less than the increase passed in
        glp_set_col_bnds(mip, m + (int) stockList->size(), GLP_DB, 0,
                         (increase->find(stock->second.getName())->second));
        glp_set_col_kind(mip, m + (int) stockList->size(), GLP_BV);

        m++;
    }
    // For when you add the Z
    // glp_set_col_bnds(mip, var + m - 3, GLP_LO, 0 , 0);


    int j = 1; //Array index
    i = 1; //constraint index

    //eq1(i)..        a(i) * Y(i) * b * L - X(i) =L= 0;  numSt eqs            //Lower bound on stocks bought
    for (int t = 1; t < numVars + 1; t++) {
        //Loops through the variables
        i = 1;
        for (stock = stockList->begin(); stock != stockList->end(); stock++) {
            //First if: X(i), second if: Y(i), third if: both when they need to be 0 for constraint
            if (i == t && t < (int) stockList->size() + 1) {
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = -1; //sets all stocks to -1
                j++;
            } else if (i + (int) stockList->size() == t) {
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = totalBudget * lowerPercentLimit;
                j++;
            } else {
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = 0; //sets all stocks to 0 if not in the equation
                j++;
            }
            //Goes to next var
            i++;
        }
    }

    int end = i;

    //eq2(i)..        a(i) * Y(i) * b * U - X(i)=G= 0;                 numSt eqs            //Upper bound on stocks bought
    for (int t = 1; t < numVars + 1; t++) {
        //Loops through the variables
        i = end;
        //Loops through the variables
        for (stock = stockList->begin(); stock != stockList->end(); stock++) {
            //Fist if: X(i), second if: Y(i), third if: both when they need to be 0 for constraint
            if (i - (int) stockList->size() == t && t < (int) stockList->size() + 1) {
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = -1; //sets all stocks to -1
                j++;
            } else if (i == t) {
                //Initializing Y
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = totalBudget * upperPercentLimit;
                j++;
            } else {
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = 0; //sets all stocks to 0 if not in the equation
                j++;
            }
            //Goes to next constraint
            i++;

        }
    }

    //eq3..           sum(i, Y(i)) - N * Z=G= 0;                       1 eq            //Have to purchase more than N stocks
    //NO Z FOR NOW UNTIL ADDED
    for (int t = 1; t < numVars + 1; t++) {
        //First if: Y(i), second if: Z WHEN ADDED, third if: The rest
        if (t > (int) stockList->size() && t != numVars) {
            //This is the sum part
            ia[j] = i; //Loops through constraints
            ja[j] = t; //Loops through variables
            ar[j] = 1; //sets all stocks to 1
            j++;
        } else if (t == numVars) {
            //This is the Z term
            ia[j] = i; //Loops through constraints
            ja[j] = t; //Loops through variables
            //ar[j] = -numDiffPurchased;
            ar[j] = 0;
            j++;
        } else {
            ia[j] = i; //Loops through constraints
            ja[j] = t; //Loops through variables
            ar[j] = 0; //sets all stocks to 0 if not in the equation
            j++;
        }
    }
    i++;

    //eq5..           sum(i, X(i)) - b =L= 0;                           1 eq            //Upper bound on amount purchased
    for (int t = 1; t < numVars + 1; t++) {
        //Does X(i) part
        if (t < (int) stockList->size() + 1) {
            //This is the sum part
            ia[j] = i; //Loops through constraints
            ja[j] = t; //Loops through variables
            ar[j] = 1; //sets all stocks to 1
            j++;
        } else {
            ia[j] = i; //Loops through constraints
            ja[j] = t; //Loops through variables
            ar[j] = 0; //sets all stocks to 0 if not in the equation
            j++;
        }

    }
    i++;

    int varNum = 1 + (int) stockList->size();

    //eq7(i)..        Y(i) - a(i) =L= 0;
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        //Loops through the variables
        for (int t = 1; t < numVars + 1; t++) {
            //Does Y(i) part
            if (varNum == t && t > (int) stockList->size() && t != numVars) {
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = 1; //sets all stocks to -1
                j++;
            } else {
                ia[j] = i; //Loops through constraints
                ja[j] = t; //Loops through variables
                ar[j] = 0; //sets all stocks to 0 if not in the equation
                j++;
            }
        }
        //Goes to next constraint
        varNum++;
        i++;
    }

    //Printing out stuff

    //cout << 3 * (int) stockList->size() + 2 << endl;
    //Prints out matrix for testing
    //cout << "Stock: " << st->getName() << " Passed in Date: " << st->convertDate(Date) << endl;
    //for (int k = 1; k < size; k++) {
    //   cout << "k = " << k << " IA = " << ia[k] << " JA = " << ja[k] << " AR = " << ar[k] << endl;
//    }
    //for (int r = 1; r < 9; r++) {
    // cout << "Row " << r << " lb: " << glp_get_row_lb(mip,r) << endl;
    //cout << "Row " << r << " ub: " << glp_get_row_ub(mip,r) << endl;
    //}
    /*
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        cout << "Increase for stock " << stock->second.getName() << ": " << increase->find(stock->second.getName())->second << endl;
    }

    cout << "Printing percent" << endl;
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        cout << "Percent for stock " << stock->second.getName() << ": " << percentCorrect->find(stock->second.getName())->second << endl;
    }
     */

    //Load matrix into program
    glp_load_matrix(mip, size - 1, ia, ja, ar);

    //Initializes and calls the mixed integer solver
    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;
    glp_intopt(mip, &parm);

    z = glp_mip_obj_val(mip);

    //Prints out results
    printf("\nz: %f\n", z);
    int h = 1;
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        if (glp_mip_col_val(mip, h) > 0) {
            cout << "X(" << stock->second.getName() << "): " << glp_mip_col_val(mip, h) << endl;
        }
        results[h] = glp_mip_col_val(mip, h);
        h++;
    }
    cout << endl;
    for (stock = stockList->begin(); stock != stockList->end(); stock++) {
        if (glp_mip_col_val(mip, h) > 0) {
            cout << "Y(" << stock->second.getName() << "): " << glp_mip_col_val(mip, h) << endl;
        }
        //results[h] = glp_mip_col_val(mip, h);
        h++;
    }
    cout << "Z: " << glp_mip_col_val(mip, h) << endl;

    glp_delete_prob(mip);

    cout << "END selectStockDistribution in algorithm" << endl;

    return results;


}