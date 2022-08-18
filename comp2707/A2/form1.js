/**
 * COMP2707 - Assignment 2, Task 1
 * Developer: Dennis Dao
 * June 8, 2022
 * v1.0
 */

// Check if inputs are OK
// AngularJS is handling most of this in the HTML, this script handles future birthdays and country still selected as Country
function verifyInputs(form){
    const today = new Date();

    // Form values
    country = form.country.value;
    birthday = form.birthday.value;

    // Birthday is a day in the future
    if(birthday > today.toISOString().split('T')[0]){
        alert("\nThe selected birth date is invalid. Please select a date that has already occurred.");
        return false;
    }

    // Country wasn't selected (still on the unselectable default value - Country)
    else if(country == "Country"){
        alert("\nA country was not selected. Please select a country from the dropdown list and ensure the selected country is not \"Country\".");
        return false;
    }
    // All OK.
    else{
        alert("Thank you for registering.");
        return true;
    }
}
