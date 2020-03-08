#include <iostream>
#include <fstream>
#include "request/request.hpp"

using namespace std;
using namespace http;

int main()
{
    
    string username, password; // defined input strings
    
    cout << "enter your username:" << endl; // asking for the username
    cin >> username; // storing the entered username
    cout << "enter your password:" << endl; // asking for the password
    cin >> password; // storing the entered password

    try
    {
        Request request("http://xenforo.gandaa.lv/index.php/api/auth"); // xenforo api url

        // making the post request
        const Response postResponse = request.send("POST", "login=" + username + "&password=" + password, {
             "Content-Type: application/x-www-form-urlencoded", "XF-Api-Key: TqfDwgHw3dpuXGXC9MqVdWRmhJUic9BO" // your xenforo api key
            });

        cout << string(postResponse.body.begin(), postResponse.body.end()) << endl; // print the result

        system("pause"); // wait for user input
    }
    catch (const exception & e)
    {
        cerr << "Request failed, error: " << e.what() << endl; // print any request errors

        system("pause"); // wait for user input

        return EXIT_FAILURE; //exit programm with status code 1
    }

    return EXIT_SUCCESS; //exit programm with status code 0
}