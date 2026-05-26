// 15 fixation problems on the topic of Conditionals Operators

// Problem 1 - Conditionals (Easy)

// Declare an int called temperature = 35.

// If temperature is above 30, print "It's hot!"
// If it's between 15 and 30, print "It's comfortable!"
// Otherwise print "It's cold!"

#include <stdio.h>

int main()
{

    int temperature = 35;

    if (temperature > 30)
    {
        printf("It's hot!");
    }
    else if (temperature < 30 && temperature > 15)
    {
        printf("It's comfortable!");
    }
    else
    {
        printf("It's cold");
    }

    return 0;
}

// Problem 2 — Conditionals (Easy)
// Declare an int called score = 72.

// If score is 90 or above, print "Grade: A"
// If score is 80 or above, print "Grade: B"
// If score is 70 or above, print "Grade: C"
// Otherwise print "Grade: F"

#include <stdio.h>

int main()
{

    int score = 72;

    if (score >= 90)
    {
        printf("Grade: A");
    }
    else if (score >= 80)
    {
        printf("Grade: B");
    }
    else if (score >= 70)
    {
        printf("Grade: C");
    }
    else
    {
        printf("Grade: F");
    }

    return 0;
}

// Problem 3 — Conditionals (Easy)Problem 3 — Conditionals (Easy)
// Declare an int called number = 7.

// If the number is even, print "Even"
// If the number is odd, print "Odd"

// Hint: think about what operator tells you if a number divides evenly!

#include <stdio.h>

int main()
{

    int num = 8;

    if (num % 2 == 0)
    {
        printf("Even");
    }
    else
    {
        printf("Odd");
    }

    return 0;
}

// Problem 4 — Conditionals (Easy)
// Declare two int variables, a = 15 and b = 22.

// Print which one is bigger
// If they are equal, print "They are equal"

#include <stdio.h>

int main()
{

    int a = 15;
    int b = 22;

    if (b > a)
    {
        printf("B is bigger");
    }
    else if (a > b)
    {
        printf("A is bigger");
    }
    else
    {
        printf("They are equal");
    }

    return 0;
}

// Problem 5 — Conditionals (Easy)
// Declare an int called hour = 14 (using 24h format).

// If hour is between 6 and 12, print "Good morning!"
// If hour is between 12 and 18, print "Good afternoon!"
// If hour is between 18 and 24, print "Good evening!"
// Otherwise print "You should be sleeping!"

#include <stdio.h>

int main()
{

    int hour = 14;

    if (hour >= 6 && hour <= 12)
    {
        printf("Good morning!");
    }
    else if (hour >= 12 && hour <= 18)
    {
        printf("Good afternoon!");
    }
    else if (hour >= 18 && hour <= 24)
    {
        printf("Good evening!");
    }
    else
    {
        printf("You should be sleeping!");
    }

    return 0;
}

// Problem 6 — Conditionals (Intermediate)Problem 6 — Conditionals (Intermediate)
// Declare:

// int age = 17
// int has_id = 1 (remember, in C 1 means true, 0 means false)
// If the person is 18 or older AND has an id, print "Welcome in!"
// If the person is 18 or older but has NO id, print "Need to see your ID!"
// If the person is under 18, print "You are too young!"

int main()
{
    int age = 17;

    int has_id = 1;

    if (age >= 18 && has_id)
    {
        printf("Welcome in!");
    }
    else if (age >= 18 && has_id == 0)
    {
        printf("Need to see your ID!");
    }
    else
    {
        printf("You are too young.");
    }

    return 0;
}

// Problem 7 — Conditionals (Intermediate)
// Declare:

// float bmi = 22.5

// Print the BMI category:

// Below 18.5 → "Underweight"
// Between 18.5 and 24.9 → "Normal weight"
// Between 25.0 and 29.9 → "Overwei

#include <stdio.h>

int main()
{

    float bmi = 22.5;

    if (bmi <= 18.5)
    {
        printf("Underweight");
    }
    else if (bmi >= 18.5 && bmi <= 24.9)
    {
        printf("Normal weight");
    }
    else if (bmi >= 25.0 && bmi <= 29.9)
    {
        printf("Overweight");
    }
    else
    {
        printf("Obese");
    }

    return 0;
}

// Problem 8 — Conditionals (Intermediate)Problem 8 — Conditionals (Intermediate)
// Declare:

// int hour = 14
// int is_weekend = 0
// If it's a weekend and before 10, print "Sleeping in!"
// If it's a weekend and 10 or after, print "Weekend day!"
// If it's a weekday and before 9, print "Early bird!"
// If it's a weekday and between 9 and 17, print "Working hours!"
// Otherwise print "Evening time!"

#include <stdio.h>

int main()
{

    int hour = 14;
    int is_weekend = 0;

    if (is_weekend == 1 && hour < 10)
    {
        printf("Sleeping in!");
    }
    else if (is_weekend == 1 && hour >= 10)
    {
        printf("Weekend day!");
    }
    else if (!is_weekend && hour < 9)
    {
        printf("Early bird!");
    }
    else if (!is_weekend && hour >= 9 && hour <= 17)
    {
        printf("Working hours!");
    }
    else
    {
        printf("Evening time!");
    }

    return 0;
}

// Problem 9 — Conditionals (Intermediate)Problem 9 — Conditionals (Intermediate)
// Declare:

// int units_sold = 85
// float base_salary = 1500.0
// float commission_rate = 0.05

// A salesperson earns their base salary plus commission on units sold. But:

// If they sold more than 100 units, commission rate is 8%
// If they sold between 50 and 100 units, commission rate is 5%
// If they sold less than 50 units, no commission
// Print the final commission rate applied
// Print the commission earned
// Print the total salary

#include <stdio.h>

int main()
{

    int units_sold = 85;
    float base_salary = 1500.0;
    float commission_rate = 0.05;

    if (units_sold > 100)
    {
        commission_rate = 0.08;
    }
    else if (units_sold >= 50 && units_sold <= 100)
    {
        commission_rate = 0.05;
    }
    else
    {
        commission_rate = 0;
    }

    float commission_earned = base_salary * commission_rate;
    float total_salary = base_salary + commission_earned;

    printf("Final commission rate: %f\n", commission_rate);
    printf("Commission earned: %f\n", commission_earned);
    printf("Total salary: %f\n", total_salary);

    return 0;
}

// Problem 10 — Conditionals (Intermediate)
// Declare:

// int player_health = 45
// int enemy_health = 80
// int player_attack = 25
// int enemy_attack = 15
// int player_has_shield = 1
// Rules:

// If player has a shield, enemy attack is reduced by 50%
// If player health is below 50, player attack is increased by 10 (desperation boost)
// If enemy health drops to 0 or below after player attack, print "Enemy defeated!"
// If player health drops to 0 or below after enemy attack, print "Player defeated!"
// Otherwise print both remaining health values
// Think about the order of operations here — shields and boosts need to be calculated before the attacks land!

#include <stdio.h>

int main()
{

    int player_health = 45;
    int enemy_health = 80;
    int player_attack = 25;
    int enemy_attack = 15;
    int player_has_shield = 1;

    if (player_has_shield != 0)
    {
        enemy_attack = enemy_attack / 2;
    }

    if (player_health < 50)
    {
        player_attack = player_attack + 10;
    }

    enemy_health = enemy_health - player_attack;
    player_health = player_health - enemy_attack;

    if (enemy_health <= 0)
    {
        printf("Enemy is defeated!");
    }
    else if (player_health <= 0)
    {
        printf("Player is defeated!")
    }
    else
    {
        printf("Enemy health remaining: %d\n", enemy_health);
        printf("Player health remaining: %d\n", player_health);
    }

    return 0;
}

// Problem 11 — Conditionals (Hard)Problem 11 — Conditionals (Hard)
// A bank applies different interest rates based on account balance and customer type:
// Declare:

// float balance = 7500.0
// int is_premium_customer = 1

// Rules:

// Premium customer with balance above 10000 → 5% interest
// Premium customer with balance 5000 to 10000 → 3.5% interest
// Premium customer with balance below 5000 → 2% interest
// Regular customer with balance above 10000 → 3% interest
// Regular customer with balance 5000 to 10000 → 2% interest
// Regular customer with balance below 5000 → 1% interest
// Print the interest rate applied
// Print the interest earned
// Print the final balance after interest

#include <stdio.h>

int main()
{
    float balance = 7500.0;
    int is_premium_customer = 1;
    float interest_rate = 0;

    if (is_premium_customer != 0 && balance > 10000)
    {
        interest_rate = 0.05;
    }
    else if (is_premium_customer != 0 && balance >= 5000 && balance <= 10000)
    {
        interest_rate = 0.035;
    }
    else if (is_premium_customer != 0 && balance < 5000)
    {
        interest_rate = 0.02;
    }
    else if (!is_premium_customer && balance > 10000)
    {
        interest_rate = 0.03;
    }
    else if (!is_premium_customer && balance >= 5000 && balance <= 10000)
    {
        interest_rate = 0.02;
    }
    else if (!is_premium_customer && balance < 5000)
    {
        interest_rate = 0.01;
    }
    else
    {
        printf("No interest rate applied.");
    }

    float interest_earned = balance * interest_rate;
    float final_balance = balance + interest_earned;

    printf("Interest rate applied: %f\n", interest_rate);
    printf("Interest earned: %f\n", interest_earned);
    printf("Final balance: %f\n", final_balance);

    return 0;
}

// Problem 12 — Conditionals (Hard)
// A traffic light system:
// Declare:

// int red = 0
// int yellow = 0
// int green = 1
// int is_emergency_vehicle = 0

// Rules:

// If an emergency vehicle is present, always print "Clear the road!" regardless of light color
// If green is on, print "Go!"
// If yellow is on, print "Slow down!"
// If red is on, print "Stop!"
// If somehow none of the lights are on, print "Light malfunction!"

#include <stdio.h>

int main()
{

    int red = 0;
    int yellow = 0;
    int green = 1;
    int is_emergency_vehicle = 0;

    if (is_emergency_vehicle != 0)
    {
        printf("Clear the road!");
    }

    if (green != 0)
    {
        printf("Go!");
    }
    else if (yellow != 0)
    {
        printf("Slow down!");
    }
    else if (red != 0)
    {
        printf("Stop!");
    }
    else
    {
        printf("Light malfunction!");
    }

    return 0;
}

/// Problem 13 — Conditionals (Hard)
// A login system:
// Declare:

// int correct_pin = 1234
// int entered_pin = 1234
// int attempts = 3
// int is_account_locked = 0

// Rules:

// If account is locked, print "Account locked! Contact support." and ignore everything else
// If attempts is 0, lock the account (set is_account_locked = 1) and print "Too many attempts! Account locked."
// If entered pin is correct, print "Access granted!"
// If entered pin is wrong and attempts are above 0, print how many attempts are remaining after this one
// If attempts drop to 0 after a wrong pin, print "Account locked!"

#include <stdio.h>

int main()
{

    int correct_pin = 1234;
    int entered_pin = 1234;
    int attempts = 3;
    int is_account_locked = 0;

    if (is_account_locked != 0)
    {
        printf("Account locked. Contact support.");
    }

    if (entered_pin == correct_pin)
    {
        printf("Access granted");
    }

    if (entered_pin != correct_pin)
    {
        attempts = attempts - 1;
        if (attempts == 0)
        {
            printf("Too many attempts! Account locked.");
            is_account_locked = 1;
        }
        else
        {
            printf("Remaning attemps left: %d\n", attempts);
        }
    }

    return 0;
}

// Problem 14 — Conditionals (Hard)Problem 14 — Conditionals (Hard)
// A simple tax calculator:
// Declare:

// float income = 55000.0
// int is_married = 1
// int has_dependents = 2

// Rules:

// Married people get a $2000 deduction
// Each dependent gets a $500 deduction
// Deductions are subtracted from income before calculating tax
// Taxable income tax rates:

// Below 20000 → 10%
// 20000 to 50000 → 20%
// Above 50000 → 30%

// Print the total deductions
// Print the taxable income (income after deductions)
// Print the tax rate applied
// Print the tax owed
// Print the final income after tax

#include <stdio.h>

    int main()
{

    float income = 550000.0;
    int is_married = 1;
    int has_dependents = 2;

    int married_deduction = 2000;
    int dependents_deduction = has_dependents * 500;
    int total_deduction = 0;

    if (is_married != 0)
    {
        total_deduction = married_deduction + dependents_deduction;
    }
    else
    {
        total_deduction = dependents_deduction;
    }

    int taxable_income = income - total_deduction;
    float tax_rate = 0;

    if (taxable_income <= 20000)
    {
        tax_rate = 0.10;
    }
    else if (taxable_income >= 20000 && taxable_income <= 50000)
    {
        tax_rate = 0.20;
    }
    else
    {
        tax_rate = 0.30;
    }

    float tax_owed = taxable_income * tax_rate;
    float final_income = income - tax_owed;

    printf("Total deduction: %d\n", total_deduction);
    printf("Taxable income: %d\n", taxable_income);
    printf("Tax applied: %f\n", tax_rate);
    printf("Tax owed: %f\n", tax_owed);
    printf("Final income: %f\n", final_income)

        return 0;
}

// Problem 15 — Conditionals (Hard)Problem 15 — Conditionals (Hard)
// A simple shipping cost calculator:
// Declare:

// float weight = 4.5 (kg)
// float distance = 350.0 (km)
// int is_fragile = 1
// int is_express = 0

// Rules:

// Base shipping cost is weight * distance * 0.01
// If fragile, add 15% to the base cost
// If express, add 25% to the base cost
// If both fragile and express, add 35% to the base cost (not 40% — it's a combined discount)
// If weight is above 10kg, add a $5.00 heavy item fee
// If distance is above 500km, add a $10.00 long distance fee
// Print the base cost
// Print the total surcharges added
// Print the final shipping cost

#include <stdio.h>

int main() {

float weight = 4.5;
float distance = 350.0;
float base_shipping_cost = weight * distance * 0.01;

int is_fragile = 1;
int is_express = 0;

float tax_per_condition = 0;

if (is_fragile && is_express) {
    tax_per_condition = 0.35;
} else if (is_fragile) {
    tax_per_condition = 0.15;
} else if (is_express) {
    tax_per_condition = 0.25;
}

float item_fee = 0;
float distance_fee = 0;

if (weight > 10) {
    item_fee = 5.00;
}

if (distance > 500) {
    distance_fee = 10.00;
}

float total_supercharges = (base_shipping_cost * tax_per_condition) + item_fee + distance_fee;
float final_cost = base_shipping_cost + total_supercharges;

printf("Base cost: %f\n", base_shipping_cost);
printf("Total supercharge: %f\n", total_supercharges);
printf("Final shipping cost: %f\n", final_cost);

return 0;
}