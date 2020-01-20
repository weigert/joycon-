//Simple Bluetooth Test
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <iostream>
#include <tinyb.hpp>
#include <vector>
#include <thread>
#include <atomic>
#include <csignal>

using namespace tinyb;

/*

  Bluetooth Namespace offers a number of functions for dealing with bluetooth connections to these objects!!

  You can list all available joycons, connect to the joycons and disconnect from the joycons (bluetooth).

*/

namespace bluetooth{

  /*
    findJoycons - List all identified blutooth objects that are joycons!!
  */

  bool findJoycons(){
    std::cout<<"Finding available joycons..."<<std::endl;
    bool found = false;
    int nfound = 0;

    //Inquiry Info Object!!
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    //Open the Connection to the Local Bluetooth Device
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    //Create Storage for the Query Data
    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    //Do an inquiry on the local device for visible bluetooth devices!
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("hci_inquiry");

    //Loop over the devices and output the information!!
    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));

        /* No Name Found */
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0)
          continue;

        /* Create a String of the Name */
        std::string s(name);
        if(s.find("Joy-Con") != std::string::npos){
          found = true;
          nfound++;
          printf("%s %s\n", name, addr);
        }
    }

    if(!found) std::cout<<"No available Joycons found."<<std::endl;
    else std::cout<<"Found ("<<nfound<<") joycons."<<std::endl;
    free( ii );
    close( sock );
    return true;
  }

  /*

    connect - connect to a certain joycon object!
    disconnect - disconnect to a certain joycon object!

  */

  bool connect(std::string identifier){
    /* Setup the Bluetooth Manager Interface */
    BluetoothManager *manager = nullptr;
     try {
       manager = BluetoothManager::get_bluetooth_manager();
     } catch(const std::runtime_error& e) {
         std::cerr << "Error while initializing libtinyb: " << e.what() << std::endl;
         exit(1);
     }

     /* Start the discovery of devices */
     bool ret = manager->start_discovery();
     if(!ret){
       std::cout<<"Failed to launch bluetooth discovery."<<std::endl;
       return 0;
     }

     //Current Bluetooth Device!
     BluetoothDevice *device = NULL;

     //User Message
     if(identifier == "") std::cout<<"Connecting to all Joycons."<<std::endl;
     else std::cout<<"Connecting to Joycon with ID "<<identifier<<std::endl;

     bool found = false;

     //Loop over list of found devices...
     for (int i = 0; i < 15; ++i) {

       //Make sure this is inside the retry loop...
       auto list = manager->get_devices();
       for (auto it = list.begin(); it != list.end(); ++it) {
          if(identifier == ""){
            //Connect to all Joycon Devices (i.e. check for joycon in name)!
            if( (*it)->get_name().find("Joy-Con") != std::string::npos ){
              found = true;
              device = (*it).release();
              std::cout<<"Connecting to device "<<device->get_name()<<std::endl;
              if(device == nullptr) std::cout<<"Failed to connect to device."<<std::endl;
              else{
                device->connect();
                std::cout<<"Connected to Device."<<std::endl;
              }
            }
          }
          else{
            //Connect to the ones that match the identifier!
            if( (*it)->get_address() == identifier ){
              device = (*it).release();
              std::cout<<"Connecting to device "<<device->get_name()<<std::endl;
              if(device == nullptr){
                std::cout<<"Failed to connect to device."<<std::endl;
                return false;
              }
              else{
                device->connect();
                std::cout<<"Connected to Device."<<std::endl;
                ret = manager->stop_discovery();
                return true;
              }
            }
          }
        }

        //Wait a moment...
        std::this_thread::sleep_for(std::chrono::seconds(4));
        if(found) break;
      }

     /* Stop the discovery */
     if(!found) std::cout<<"No joycons found."<<std::endl;

     ret = manager->stop_discovery();
    return true;
  }

  bool disconnect(std::string identifier){
    /* Setup the Bluetooth Manager Interface */
    BluetoothManager *manager = nullptr;
     try {
       manager = BluetoothManager::get_bluetooth_manager();
     } catch(const std::runtime_error& e) {
         std::cerr << "Error while initializing libtinyb: " << e.what() << std::endl;
         exit(1);
     }

     /* Start the discovery of devices */
     bool ret = manager->start_discovery();
     if(!ret){
       std::cout<<"Failed to launch bluetooth discovery."<<std::endl;
       return 0;
     }

     //Current Bluetooth Device!
     BluetoothDevice *device = NULL;

     //User Message
     if(identifier == "") std::cout<<"Disconnecting from all Joycons."<<std::endl;
     else std::cout<<"Disconnecting from Joycon with ID "<<identifier<<std::endl;

     bool found = false;

     //Loop over list of found devices...
     for (int i = 0; i < 15; ++i) {

       //Make sure this is inside the retry loop...
       auto list = manager->get_devices();
       for (auto it = list.begin(); it != list.end(); ++it) {
          if(identifier == ""){
            //Connect to all Joycon Devices (i.e. check for joycon in name)!
            if( (*it)->get_name().find("Joy-Con") != std::string::npos ){
              found = true;
              device = (*it).release();
              std::cout<<"Disconnecting from device "<<device->get_name()<<std::endl;
              if(device == nullptr) std::cout<<"Failed to connect to device."<<std::endl;
              else{
                device->disconnect();
                std::cout<<"Disconnected from device."<<std::endl;
              }
            }
          }
          else{
            //Connect to the ones that match the identifier!
            if( (*it)->get_address() == identifier ){
              device = (*it).release();
              std::cout<<"Disconnecting from device "<<device->get_name()<<std::endl;
              if(device == nullptr){
                std::cout<<"Failed to disconnect from device."<<std::endl;
                return false;
              }
              else{
                device->disconnect();
                std::cout<<"Disconnected from device."<<std::endl;
                ret = manager->stop_discovery();
                return true;
              }
            }
          }
        }

        //Wait a moment...
        std::this_thread::sleep_for(std::chrono::seconds(4));
        if(found) break;
      }

     /* Stop the discovery */
     if(!found) std::cout<<"No joycons found."<<std::endl;

     ret = manager->stop_discovery();
    return true;
  }
};
