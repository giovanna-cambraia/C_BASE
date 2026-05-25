// 15 fixation problems on the topic of Arithmetic Operators

// Problem 1 - Arithmetic Operators (Easy)

// Declare two int variables, x = 15 and y = 4. Then:

// Print their sum
// Print their difference
// Print the result of dividing x by y as a decimal (so you'll need to think about the integer division trap)
// Print the remainder of that division

#include <stdio.h>

int main()
{

    int x = 15;

    printf("Sum: %d\n", x + y);
    printf("Difference: %d\n", x - y);
    printf("Division: %f\n", (float)x / y);
    printf("Remainder: %d\n", x % y);

    return 0;
}

// Problem 2 — Arithmetic Operators (Easy)
// Declare two int variables, apples = 10 and baskets = 3.

// Print how many apples go in each basket (integer division, whole number result is fine here)
// Print how many apples are left over after filling the baskets equally

#include <stdio.h>

int main()
{

    int apples = 10;
    int baskets = 3;

    printf("In each basket: %d\n", apples / baskets);
    printf("Left over: %d\n", apples % baskets);

    return 0;
}

// Problem 3 — Arithmetic Operators (Easy)Problem 3 — Arithmetic Operators (Easy)
// Declare three int variables: length = 8, width = 5, height = 3.

// Print the area of the base (length × width)
// Print the volume (length × width × height)

#include <stdio.h>

int main()
{

    int length = 8;
    int width = 5;
    int height = 3;

    printf("Area of the base: %d\n", length * width);
    printf("Volume: %d\n", length * width * height);

    return 0;
}

// Problem 4 — Arithmetic Operators (Easy)
// You have a float called price = 9.99 and an int called quantity = 4.

// Print the total cost
// Print the average cost per item if you had spent 50.0 on the same item instead (so 50.0 / quantity)

#include <stdio.h>

int main()
{

    float price = 9.99;
    int quantity = 4;
    float average_cost = 50.0;

    printf("Total cost: %f\n", price * quantity);
    printf("Average cost: %f\n", average_cost / quantity);

    return 0;
}

// Problem 5 — Arithmetic Operators (Easy)
// Declare an int called seconds = 3661.

// Print how many hours are in that many seconds
// Print how many minutes are left over after extracting the hours
// Print how many seconds are left over after extracting the minutes

#include <stdio.h>
int main()
{

    int seconds = 3661;
    int hours = seconds / 3600;
    int remainingSeconds = seconds % 3600;
    int minutes = remainingSeconds / 60;
    int finalSeconds = remainingSeconds % 60;

    printf("Hours: %d\n", hours);
    printf("Minutes: %d\n", minutes);
    printf("Seconds: %d\n", finalSeconds);

    return 0;
}

// Problem 6 — Arithmetic Operators (Intermediate)Problem 6 — Arithmetic Operators (Intermediate)
// A store is having a sale. Declare:

// float original_price = 80.0
// int discount_percent = 15
// Print the discount amount (how much money you save)
// Print the final price after the discount

#include <stdio.h>
int main()
{

    float originalPrice = 80.0;
    float discountPercent = 15.0;
    int discountAmount = 12;

    printf("Discount amount: %f\n", originalPrice * (discountPercent / 100));
    printf("Final price: %f\n", originalPrice - discountAmount);

    return 0;
}

// Problem 7 — Arithmetic Operators (Intermediate)
// Declare:

// int total_students = 30
// int passing_students = 22
// Print the percentage of students passing as a decimal (ex: 73.333...)
// Print how many are failing

#include <stdio.h>

int main()
{

    int total_students = 30;
    int passing_students = 22;

    printf("Percentage of passing students: %f\n", (float)passing_students / total_students * 100);
    printf("Percentage of failing students: %d\n", total_students - passing_students);

    return 0;
}

// Problem 8 — Arithmetic Operators (Intermediate)
// Declare:

// int kilometers = 42
// Print how many meters that is (1 km = 1000 m)
// Print how many centimeters that is
// Print how many miles that is as a decimal (1 km = 0.621371 miles) — you'll need a float for this one

#include <stdio.h>

int main()
{

    int kilometers = 42;
    int metersInKm = kilometers * 1000;
    int metersToCm = metersInKm * 100;
    float KmToMiles = kilometers * 0.621371;

    printf("Meters in KM: %d\n", metersInKm);
    printf("Meters to CM: %d\n", metersToCm);
    printf("KM to Miles: %f\n", KmToMiles);

    return 0;
}

// Problem 9 — Arithmetic Operators (Intermediate)Problem 9 — Arithmetic Operators (Intermediate)
// Declare:

// int age = 28
// Print how many months that is
// Print how many days that is (assume 365 days per year)
// Print how many hours that is
// Print how many seconds that is

#include <stdio.h>

int main()
{

    int age = 28;
    int months_in_age = age * 12;
    int days_in_age = age * 365;
    int hours_in_age = days_in_age * 24;
    int seconds_in_age = hours_in_age * 60 * 60;

    printf("Months in age: %d\n", months_in_age);
    printf("Days in age: %d\n", days_in_age);
    printf("Hours in age: %d\n", hours_in_age);
    printf("Seconds in age: %d\n", seconds_in_age);

    return 0;
}

// Problem 10 — Arithmetic Operators (Intermediate)
// Declare:

// float celsius = 36.6
// Print the temperature converted to Fahrenheit
// Print the temperature converted to Kelvin

// The formulas are:

// Fahrenheit: (celsius * 9/5) + 32
// Kelvin: celsius + 273.15

#include <stdio.h>

int main()
{

    float celsius = 36.6;
    float fahrenheit = (celsius * 9 / 5.0) + 32;
    float kelvin = celsius + 273.15;

    printf("Fahrenheit to celsius: %f\n", fahrenheit);
    printf("Kelvin to celsius: %f\n", kelvin);

    return 0;
}

// Problem 11 — Arithmetic Operators (Hard)
// A car travels at float speed = 80.5 km/h for float time = 2.5 hours.

// Print the distance traveled (speed × time)
// Print how many minutes the trip took
// Print how many meters the distance is
// Print the average speed in meters per second

#include <stdio.h>

int main()
{

    float speed = 80.5;
    float time = 2.5;
    float distance_traveled = speed * time;
    float minutes_traveled = time * 60;
    float meters_traveled = distance_traveled * 1000;
    float seconds_traveled = time * 60 * 60;
    float avg_speed_persecond = meters_traveled / seconds_traveled;

    printf("Distance traveled: %f\n", distance_traveled);
    printf("Minutes traveled: %f\n", minutes_traveled);
    printf("Distance in meters: %f\n", meters_traveled);
    printf("Average speed in meters per second: %f\n", avg_speed_persecond);

    return 0;
}

// Problem 12 — Arithmetic Operators(Hard) Problem 12 — Arithmetic Operators(Hard)
// A shop sells three products:

// float price_a = 12.99
// float price_b = 7.49
// float price_c = 3.99

// A customer buys int qty_a = 3, int qty_b = 5, int qty_c = 2.

// Print the subtotal for each product (price × quantity)
// Print the total of all three subtotals
// Print the average price per item across the entire purchase (total / total items bought)
// Print the tax amount (8.5% of the total)
// Print the final price including tax

#include <stdio.h>

int main()
{

    float price_a = 12.99;
    float price_b = 7.49;
    float price_c = 3.99;

    int qty_a = 3;
    int qty_b = 5;
    int qty_c = 2;

    // subtotal for each quantity

    float subtotal_1 = price_a * qty_a;
    float subtotal_2 = price_b * qty_b;
    float subtotal_3 = price_c * qty_c;

    float subtotal_all = subtotal_1 + subtotal_2 + subtotal_3;

    float avg_price_peritem = subtotal_all / (qty_a + qty_b + qty_c);

    float tax_amount = avg_price_peritem * 8.5 / 100;
    float final_price = subtotal_all + tax_amount;

    printf("Subtotal for product_1: %f\n", subtotal_1);
    printf("Subtotal for product_2: %f\n", subtotal_2);
    printf("Subtotal for product_3: %f\n", subtotal_3);
    printf("Total of all three subtotals: %f\n", subtotal_all);
    printf("Average price per item: %f\n", avg_price_peritem);
    printf("Tax amount: %f\n", tax_amount);
    printf("Final price: %f\n", final_price);

    return 0;
}

// Problem 13 — Arithmetic Operators (Hard)
// You're splitting a restaurant bill:

// float bill = 143.50
// int people = 4
// float tip_percent = 18.0
// Print the tip amount
// Print the total bill including tip
// Print each person's share of the total
// Print each person's share rounded down to the nearest cent — meaning just 2 decimal places is fine, %.2f works as a format specifier for that!

#include <stdio.h>

int main()
{

    float bill = 143.50;
    int people = 4;
    float tip_percent = 18.0;

    float tip_amount = bill * (tip_percent / 100);
    float total_bill = bill + tip_amount;
    float each_person_share = total_bill / people;

    printf("Tip amount: %f\n", tip_amount);
    printf("Total bill: %f\n", total_bill);
    printf("Each person's share: %f\n", each_person_share);
    printf("Each person's share rounded: %.2f\n", each_person_share);

    return 0;
}

// Problem 14 — Arithmetic Operators (Hard)
// You're calculating how long it takes two cars to meet. Car A starts from city 1 and Car B starts from city 2, driving toward each other:

// float distance_between_cities = 320.0 (km)
// float speed_a = 90.0 (km/h)
// float speed_b = 110.0 (km/h)

// Print the combined speed of both cars approaching each other
// Print the time until they meet in hours (distance / combined speed)
// Print the time until they meet in minutes
// Print the distance car A has traveled when they meet
// Print the distance car B has traveled when they meet
// Verify your answer by printing car A distance + car B distance (should equal 320!)

#include <stdio.h>

int main()
{

    float distance_between_cities = 320.0;
    float speed_a = 90.0;
    float speed_b = 110.0;

    float combined_speed = speed_a + speed_b;
    float until_meet = distance_between_cities / combined_speed;
    float until_meet_minutes = until_meet * 60;

    float distance_traveled_a = speed_a * until_meet;
    float distance_traveled_b = speed_b * until_meet;

    printf("Combined speed: %f\n", combined_speed);
    printf("Until the cars meet in hours: %f\n", until_meet);
    printf("Until the cars meet in minutes: %f\n", until_meet_minutes);
    printf("A's traveled distance until meet: %f\n", distance_traveled_a);
    printf("B's traveled distance until meet: %f\n", distance_traveled_b);

    return 0;
}

// Problem 15 — Arithmetic Operators (Hard)
// You're managing a small cinema:

// int total_seats = 120
// int seats_sold = 93
// float ticket_price = 14.50
// float popcorn_price = 6.99
// int popcorn_sold = 67

// Print the occupancy percentage of the cinema
// Print the revenue from tickets
// Print the revenue from popcorn
// Print the total revenue
// Print the average revenue per person (total revenue / seats sold)
// Print the empty seats

#include <stdio.h>

int main()
{

    int total_seats = 120;
    int seats_sold = 93;
    float ticket_price = 14.50;
    float popcorn_price = 6.99;
    int popcorn_sold = 67;
    int empty_seats = total_seats - seats_sold;

    int occupancy_percentage = (float)seats_sold / total_seats * 100;
    float ticket_revenue = seats_sold * ticket_price;
    float popcorn_revenue = popcorn_price * popcorn_sold;
    float total_revenue = ticket_revenue + popcorn_revenue;
    float avg_revenue = total_revenue / seats_sold;

    printf("Occupancy percentage: %d\n", occupancy_percentage);
    printf("Ticket revenue: %f\n", ticket_revenue);
    printf("Popcorn revenue: %f\n", popcorn_revenue);
    printf("Total revenue: %f\n", total_revenue);
    printf("Average revenue per person: %f\n", avg_revenue);
    printf("Empty seats: %d\n", empty_seats);

    return 0;
}
