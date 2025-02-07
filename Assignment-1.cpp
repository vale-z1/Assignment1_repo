// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<string>

// Asks for an input and checks if its numerical positive integer. It does this by checking every character in the input
// string corresponds to a number 0-9.
// Returns the input if integer, otherwise keeps asking until a valid integer is given.
int integer_input_check()
{
    std::string input_variable;

    std::cin>>input_variable;

    std::string digits{"0123456789"};

    int digits_count{0};

    for (char character : input_variable) // Iterates over every character of the input string
    {

        for (char n : digits)  // Checks if any of the digits in 123456789 corresponds to the character being iterated
        {

            // If one of the digits corresponds to the iterated character then add one to digits_count
            if (character == n)
            {
                digits_count++;
                break;
            }

        }

    }

    std::size_t string_size{input_variable.length()};
    if (digits_count == string_size) // Compares the string lenght to the number of digits in the string.
    {
        int checked_integer{std::stoi(input_variable)};
        return checked_integer;
    }

    // If lenght and number of digits do not corresponds, input is not a positive integer. User is asked to input a new value
    std::cout<<input_variable<<" is not a valid integer. Please enter a valid number: "<<std::endl;

    int checked_integer{integer_input_check()};
    return checked_integer;
}


int y_n_check(std::string y_n)  // Checks and validates for y/n input
{
    if (y_n == "y" || y_n == "Y")
        {
        return 1;
        }

    if (y_n == "n" || y_n == "N")
        {
        return 2;
        }


    return 0; // Returns 0 if input neither y,Y or n,N

}


int physical_restraints(int coefficent_type, int checked_integer)  // Checks for physical constraints (different for atomic and quantum numbers)

{
    if (coefficent_type == 0)  // Coefficent type = 0 if checking for A number

    {
        if (checked_integer == 0)
        {
            std::cout<<"Please enter a non-zero value: "<<std::endl;
            return 0;
        }

        if (checked_integer > 120)
        {
            std::cout<<"The atomic number is physically too large, do you want to proceed? [y/n]: "<<std::endl;

            std::string y_n;

            // Asks user if they want to proceed with an unrealistically high atomic number
            int x{0};
            while (x == 0)  // Creates a loop which is only exited when correct [y/n] input is used
            {
                std::cin>>y_n;
                int y_n_result{y_n_check(y_n)};

                if (y_n_result == 1)
                {
                    return 1;
                }

                if (y_n_result == 2)
                    {
                        std::cout<<"Please enter a new value for the atomic number: "<<std::endl;
                        return 0;
                    }

                if (y_n_result == 0)
                    {
                        std::cout<<"For Yes and No please enter [y/n]: "<<std::endl;

                    }
            }


        }
        else return 1;

    }

    if (coefficent_type == 1)  // coefficent type = 1 to check for quantum numbers validity
    {
        if (checked_integer == 0)
        {
            std::cout<<checked_integer<<std::endl;
            std::cout<<"Please enter a non-zero value"<<std::endl;
            return 0;
        }

        else return 1;

    }

return 0;
}



int transition_energy(int ini_qn, int fin_qn, int atm_number)  // Calculates and converts (after asking to the user) the transition energy
{

    const float electronvolt{1.602e-19};
    float ini_qnf = static_cast<float>(ini_qn);
    float fin_qnf = static_cast<float>(fin_qn);
    float atm_numberf = static_cast<float>(atm_number);


    float t_energy{float(-13.6 * atm_number * atm_numberf * ((1 / (ini_qnf * ini_qnf))-(1 / (fin_qnf * fin_qnf))))};
    std::cout<<"The transition energy is = "<<t_energy<<" eV"<<std::endl;

    std::string y_n;
    std::cout<<" "<<std::endl;
    std::cout<<"Would you like to convert to Joules? [y/n]"<<std::endl;

    int x{0};
    while (x == 0)  // Loop to validate [y/n] input
    {
        std::cin>>y_n;
        int y_n_result{y_n_check(y_n)};

        if (y_n_result == 1)
        {
            float t_energy_joule{t_energy * electronvolt};
            std::cout<<"The transition energy is = "<<t_energy_joule<<" Joules"<<std::endl;
            std::cout<<"------------------------------- "<<std::endl;
            return 0;
        }

        if (y_n_result == 2)
        {
            return 0;
            std::cout<<"------------------------------- "<<std::endl;
        }

        if (y_n_result == 0)
        {
            std::cout<<"For Yes and No please enter [y/n]: "<<std::endl;
        }
    }

    return 0;
}


int main()
{
    // Prompts the user to enter a value for the atomic number
    std::cout<<"Enter a value for the atomic number: "<<std::endl;


    int flag{0};
    int* A_number_pointer= new int;

    while (flag == 0)  // Loop ends when all checks are passed, A_number is therfore fully validated.
    {
        int coef_type{0};
        *A_number_pointer = integer_input_check();
        flag = physical_restraints(coef_type, *A_number_pointer);
    }

    int A_number{*A_number_pointer};
    std::cout<<"The atomic number given is: "<<A_number<<std::endl;
    std::cout<<"------------------------------- "<<std::endl;

// ------------------------

    std::cout<<"Enter a value for the initial quantum number: "<<std::endl;
    int flag1{0};
    int* in_qnum_pointer= new int;

    while (flag1 == 0)  // Loop ends when initial q. number input is fully validated.
    {
        int coef_type{1};
        *in_qnum_pointer = integer_input_check();

        flag1 = physical_restraints(coef_type, *in_qnum_pointer);
    }

    int in_qnumber{*in_qnum_pointer};
    std::cout<<"The initial quantum number given is: "<<in_qnumber<<std::endl;
    std::cout<<"------------------------------- "<<std::endl;

// -----------------------

    std::cout<<"Enter a value for the final quantum number: "<<std::endl;
    int flag2{0};
    int* fin_qnumber_pointer= new int;

    while (flag2 == 0)  // Loop ends when final q. number input is fully validated.
    {
        int coef_type{1};
        *fin_qnumber_pointer = integer_input_check();

        flag2 = physical_restraints(coef_type, *fin_qnumber_pointer);
    }

    int fi_qnumber{*fin_qnumber_pointer};
    std::cout<<"The final quantum number given is: "<<fi_qnumber<<std::endl;
    std::cout<<"------------------------------- "<<std::endl;

    if (in_qnumber<fi_qnumber)
    {
        std::cout<<"Warning: The initial quantum number must be greater or equal to the final quantum number."<<std::endl;
        std::cout<<"The program will continue by assuming - "<<in_qnumber<<" to be the initial quantum number and - " <<fi_qnumber<<" the final quantum number"<<std::endl;
        std::cout<<"============================================================================================================"<<std::endl;
        transition_energy(fi_qnumber, in_qnumber, A_number);
    }

    else transition_energy(in_qnumber, fi_qnumber, A_number);  

    return 0;
}