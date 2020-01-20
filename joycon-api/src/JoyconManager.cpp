#include "JoyconManager.h"

/*
================================================================================
															SETUP AND CLEANUP
================================================================================
*/


bool JoyconManager::setup(){
  std::ios_base::sync_with_stdio(false);

  // Initialize the hidapi library
	if (hid_init()) {
		std::cerr << "HID initialization failed!" << std::endl;
		return false;
	}

  signal(SIGINT , SigCallback);
	signal(SIGTERM, SigCallback);

  return true;
}

//De-Initializer
void JoyconManager::cleanup(){
	/* Cleanup all Joycons! */

  //Shutdown HID
  hid_exit();
}

//Bind a Specific Joycon
bool JoyconManager::bind(std::string _serial){
	/* Make sure the Joycon Object doesn't exist! */
	for(unsigned int i = 0; i < joycons.size(); i++){
		if(joycons[i]->serial == _serial){
			std::cout<<"Joycon already bound."<<std::endl;
			return false;
		}
	}

	/* Find the Joycon with the correct Serial */
	hid_device_info* devs = hid_enumerate(JOYCON_VENDOR, 0x0);
	if (devs == nullptr) return false;

	//Loop over all Identified Bluetooth HID Devices!
	hid_device_info* cur;
	bool found = false;
	for (cur = devs; cur != nullptr; cur = cur->next) {
		//Find a Joycon Object!
		if (cur->vendor_id != JOYCON_VENDOR) continue;
		if (cur->product_id != JOYCON_L_BT && cur->product_id != JOYCON_R_BT) continue;

		/* Extract the Serial Number */
		std::wstring ws_sn(cur->serial_number);
		std::string sn(ws_sn.begin(), ws_sn.end());

		/* Found the guy!! */
		if(sn == _serial){
			found = true;
			break;
		}
	}

	if(!found){
		std::cout<<"Couldn't find Joycon!"<<std::endl;
		return false;
	}

	/* Construcut the Joycon */
	Joycon* joycon = new Joycon(static_cast<JOY_PID>(cur->product_id), cur->serial_number);
	if(!joycon->open()){
		std::cout<<"Could'nt establish connection to joycon. Probably insufficient permissions."<<std::endl;
		delete joycon;
		return false;
	}

	//Set the remaining properties!
	std::cout<<"Joycon bound successfully."<<std::endl;
	std::wstring ws_pn(cur->product_string);
	std::string pn(ws_pn.begin(), ws_pn.end());
	joycon->name = pn;
	joycons.emplace_back(joycon);

	/* Start Capturing Data and Send Command to set light! */
	joycon->set_player_lights(P0_KEEP_ON);
	std::cout<<"Starting capture..."<<std::endl;
	joycon->capture();

	hid_free_enumeration(devs);
	return true;
}

bool JoyconManager::release(std::string _serial){
	/* Make sure the Joycon Object exists... */
	for(unsigned int i = 0; i < joycons.size(); i++){
		if(joycons[i]->serial == _serial){
			std::cout<<"Unbinding Joycon..."<<std::endl;
			delete joycons[i];
			joycons.erase(joycons.begin()+i);
			return true;
		}
	}

	/* Object was not in the vector! */
	std::cout<<"Couldn't find bound joycon."<<std::endl;
	return false;
}

void JoyconManager::list(){
	/* This should list all bound devices and then all available devices! */
	std::cout<<"Bound Devices:"<<std::endl;
	if(joycons.size() == 0) std::cout<<"No Bound Devices."<<std::endl;
	else
		for(unsigned int i = 0; i < joycons.size(); i++){
			std::cout<<joycons[i]->name<<" "<<joycons[i]->serial<<std::endl;
		}

	/* Output Non-Bound Joycons! */
	std::cout<<"Available Devices:"<<std::endl;
  hid_device_info* devs = hid_enumerate(JOYCON_VENDOR, 0x0);
	if (devs == nullptr){
		std::cout<<"No Available Devices."<<std::endl;
		return;
	}

	//Loop over all Identified Bluetooth HID Devices!
  for (hid_device_info* cur = devs; cur != nullptr; cur = cur->next) {

		//Check for Non-Joycon Objects!
    if (cur->vendor_id != JOYCON_VENDOR) continue;
		if (cur->product_id == PRO_CONTROLLER) continue;
		if (cur->product_id == JOYCON_CHARGING_GRIP) continue;
		if (cur->product_id != JOYCON_L_BT && cur->product_id != JOYCON_R_BT) continue;

		//Dump the Joy-Con Info
		std::wstring ws_pn(cur->product_string);
		std::wstring ws_sn(cur->serial_number);
		std::string pn(ws_pn.begin(), ws_pn.end());
		std::string sn(ws_sn.begin(), ws_sn.end());

		std::cout<<pn<<" "<<sn<<std::endl;
  }

  hid_free_enumeration(devs);
}
