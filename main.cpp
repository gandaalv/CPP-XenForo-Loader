// windows related
#include <iostream>
#include <fstream>
#include <direct.h>
#include <cstdlib>
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
    /*
    some sidenote for the hwid check, there are for sure multiple ways for this, 
    but imo it was the easiest way to connect to the xenforo database via a php script and
    provide it through there.
    but to avoid random people fucking up the hwid system (because in the php file we won't check the password)
    we will secure the input by a token which is defined in the php file and inside the loader.
    */

    string username, password; // defined authentication strings
    string hwid, hwidtoken, respondedhwid; // hwid related strings
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
            cout << "login was successful :)" << endl;

            // now we do a staff check first, if the logged in user is a staff member, we will skip the hwid check

            if (Value* user = GetValueByPointer(document, "/user")) // since "success" and "user" are 2 different pointers, we need to resolve the second one
            {
                if ((*user)["is_staff"].GetBool() || (*user)["is_admin"].GetBool() || (*user)["is_moderator"].GetBool() || (*user)["is_super_admin"].GetBool() == true) { // we check if either one of those staff variables are true
                    cout << "staff member detected, no hwid check needed!" << endl;
                    
                    // from here the main authentication is basically done, next step would be the cheat part.
                }
                else // if the logged in user is not a staff member, continue with the hwid check
                {
                    if (Value* v = GetValueByPointer(document, "/user")) {
                        const Value& secondary_group = (*v)["secondary_group_ids"];
                        assert(secondary_group.IsArray());

                        if (secondary_group[0].GetInt() == 2 || secondary_group[0].GetInt() == 3 || secondary_group[0].GetInt() == 4 || secondary_group[0].GetInt() == 5) // kinda ghetto like, but it checks for the secondary group ids. why? because the xenforo userupgrade function only edits the secondary group id, not the primary.
                        { // the 0 defines ^^^ the position of inside the array, the other numbers define the usergroup id
                            try // try to make a second request
                            {
                                cout << "checking hwid..." << endl;

                                hwid = to_string(utils->GetHWID());
                                hwidtoken = "1337";

                                Request requesthwid("http://xenforo.gandaa.lv/hwid.php?username=" + username + "&token=" + hwidtoken + "&hwid=" + hwid); // we will use now the hwid.php for the new request

                                const http::Response getResponseHWID = requesthwid.send("GET"); // for the hwid request we only need a simple 'GET' request
                                respondedhwid = string(getResponseHWID.body.begin(), getResponseHWID.body.end());

                                if (respondedhwid == "new") // if there is no hwid set
                                {
                                    cout << "no stored hwid found! setting new one." << endl;
                                    utils->StoreLogin(username, password, hwid, appdatafile); // storing the logindata for later
                                    // do cheat stuff
                                }
                                else if (respondedhwid == "accepted") // if hwid check was successful
                                {
                                    cout << "hwid check was successful, welcome back " + username + " :)" << endl;
                                    utils->StoreLogin(username, password, hwid, appdatafile); // storing the logindata for later
                                    // do cheat stuff
                                }
                                else if (respondedhwid == "declined")
                                {
                                    cout << "unknown hwid detected! please request a reset" << endl;
                                    // don't allow to continue / exit the programm
                                }
                                else
                                {
                                    cout << "some unknown error occured, please check back later :(" << endl;
                                    // some other error within the system
                                }
                            }
                            catch (const exception & e) // catch any errors
                            {
                                cerr << "hwid request failed, error: " << e.what() << endl; // print the errors

                                system("pause"); // wait for user input

                                return EXIT_FAILURE; //exit programm with status code 1
                            }
                        }
                        else // no subscription - wrong usergroup
                        {
                            cout << "no active sub found" << endl;
                            system("pause");
                            return EXIT_FAILURE;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "login was not successful :(" << endl; // invalid username+password combination
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