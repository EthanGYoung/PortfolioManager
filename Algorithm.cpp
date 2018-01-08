//
// Created by Ethan Young on 1/1/18.
//

#include "Algorithm.h"
#include <glpk.h>
#include <iostream>

Algorithm::Algorithm() {

}

Algorithm::~Algorithm() {

}

int testInterval = 2; //The number of days to run regression on

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
void Algorithm::predictDate(Fund *fund, tm *Date, Stock *st, vector<string> *faName) {
    cout << "predictDate in algorithm" << endl;

    glp_prob *lp; //LP instance

    int size = ((int)faName->size() + testInterval * 2) * testInterval + 1;

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

    vector<tm*> *dates = fund->getDateList();
    vector<tm*>::iterator it;
    vector<string>::iterator itr;


    //Gets actuals for the bounds and goes backwards to the correct date
    cout << "Actuals loop in algorithm" << endl;
    cout << "Accessing element: " << indexVal << endl;
    for (it = dates->begin() + indexVal;  i < testInterval + 1;  it++) {
        double actual = st->getFactorValue("OpenPrice",*it);
        cout << "Actual: " << actual << endl;

        //Equality constraint
        glp_set_row_bnds(lp, i, GLP_FX, actual, actual);
        i++;
    }

    //Number variables in factor size + numConstraints*2 (2 errors for each constraint)
    int numVars = (int)(faName->size() + testInterval * 2);

    //Creates the variables
    glp_add_cols(lp, numVars);

    //Creates a free variable for every factor and 2 non neg for every constraint
    for (int j = 1; j < numVars + 1; j++) {
        if (j < (int)(faName->size() + 1)) {
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
        cout << "Factor: " << (*itr) << endl;

        //Loops through constraints and sets coefficients
        for (it = dates->begin() + indexVal; i < testInterval + 1; it++) {
            cout << "Var: " << varNum << endl;
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
        for (int k = (int)faName->size() + 1; k < 2 * testInterval + 1 + (int)faName->size(); k++) {
            //Can loop through a factor list here in the future
            ia[j] = n; //Loops through constraints
            ja[j] = k; //Loops over error variables

            //Sets coefficients for error vars
            if (k == 2 * (n - 1) + (int) faName->size() + 1) {
                ar[j] = 1.0;
            } else if (k == 2 * (n - 1) + (int) faName->size() + 2){
                ar[j] = -1.0;
            }
            else {
                ar[j] = 0;
            }

            j++;
        }
    }

    //Prints out matrix for testing
    //for (int k = 1; k < size; k++) {
    //    cout << "k = " << k << " IA = " << ia[k] << " JA = " << ja[k] << " AR = " << ar[k] << endl;
    //}

    //Load matrix into program
    glp_load_matrix(lp, size - 1, ia, ja, ar);

    glp_simplex(lp, NULL);

    z = glp_get_obj_val(lp);

    printf("\nz: %f\n", z);

    for (int h = 1; h < (int)faName->size() + 1; h++) {
        cout << "Var" << h << ": " << glp_get_col_prim(lp, h) << " ";
        results[h] = glp_get_col_prim(lp, h);
    }
    cout << endl;
    for (int h = (int)faName->size() + 1; h < (int)faName->size() + 2 * testInterval + 1; h++) {
        cout << "Error" << h << ": " << glp_get_col_prim(lp, h) << " ";
        results[h] = glp_get_col_prim(lp, h);
    }

    glp_delete_prob(lp);



}

int Algorithm::getDateIndex(tm* Date, Stock *st, Fund *fund) {
    int date = st->convertDate(Date);
    int index  = 0;


    vector<tm*> *dates = fund->getDateList();

    vector<tm*>::iterator it;
    for ( it = dates->begin(); it != dates->end(); it++ )
    {
        //Checks for matching date and returns the index to it
        if (st->convertDate(*it) == date) {
            return index;
        } else {
            index++;
        }
    }

    //If the date doesn't exist
    return -1;
}