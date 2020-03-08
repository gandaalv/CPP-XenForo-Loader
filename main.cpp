// windows related
#include <iostream>
#include <fstream>
#include <direct.h>
// request
#include "request/request.hpp"
// rapidjson
#include "rapidjson/document.h"
#include "rapidjson/pointer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
// utils
#include "utils/utils.hpp"

// using namespaces to make the code cleaner without typing everything with std:: etc
using namespace std;
using namespace http;
using namespace rapidjson;

int main()
{
    string username, password; // defined input strings
    string appdata, appdatafolder, appdatafile; // paths/file to store the authentication data locally on the host's pc
    bool success; // used later for checking our login data

    // definining the paths/file
    appdata = utils->GetAppData();
    appdatafolder = appdata + "\\loader";
    appdatafile = appdatafolder + "\\logindata.ini";

    if (!utils->dirExists(appdatafolder.c_str())) // check if the folder exists already
    _mkdir(appdatafolder.c_str()); // creating a folder inside appdata

    cout << "enter your username:" << endl; // asking for the username
    cin >> username; // getting the username as input
    cout << "enter your password:" << endl; // asking for the password
    cin >> password; // getting the password as inpout

    try // try to make a request
    {
        Request request("http://xenforo.gandaa.lv/index.php/api/auth"); // xenforo api url / request url

        // making the post request
        const Response postResponse = request.send("POST", "login=" + username + "&password=" + password, {
             "Content-Type: application/x-www-form-urlencoded", "XF-Api-Key: TqfDwgHw3dpuXGXC9MqVdWRmhJUic9BO" // your xenforo api key
            });

        // setting up the json document and parsing the output
        Document document;
        document.Parse(string(postResponse.body.begin(), postResponse.body.end()).c_str());

        assert(document["success"].IsBool()); // checking if the resonded function "success" is a bool
        success = document["success"].GetBool(); // defining our local variable "success" to be the responded bool

        if (success == true)
        {
            utils->StoreLogin(username, password, appdatafile); // storing the logindata for later
            cout << "login was successful :)" << endl;
        }
        else
        {
            cout << "login was not successful :(" << endl;
        }

        system("pause"); // wait for user input
    }
    catch (const exception & e) // catch any errors
    {
        cerr << "Request failed, error: " << e.what() << endl; // print the errors

        system("pause"); // wait for user input

        return EXIT_FAILURE; //exit programm with status code 1
    }

    return EXIT_SUCCESS; //exit programm with status code 0
}