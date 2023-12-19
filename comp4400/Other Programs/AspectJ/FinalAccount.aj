public aspect FinalAccount{
    // Runs as usual
    void around(): call(* *.credit(..)){ proceed();}

    // Runs with balance set to 1100

    /*
    Around notes
        The parameter in the around(..) should be an argument/value used in the function of interest. 
        Arguments can indicate passing to function
    */
    /*void around(float amount): call(* *.credit(float)) && args(amount) { 
        proceed(amount+1000); 
    }*/

    /*
    // Skips the debit call
    void around(): call(* *.debit(..)){ }
    */

    // Proceed with credit twice
    void around(): call(* *.credit(float)){ 
        proceed(); proceed();
    }

}