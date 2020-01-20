#pragma once
#include "../fwd/buffer.fwd.h"
#include "../fwd/homelight.fwd.h"

#include <queue>

#define THROW(x) throw(std::runtime_error(std::string(__FILE__) + " - line " + std::to_string(__LINE__) + ": " + __FUNCTION__ + "(): " + x ))
#define CHECK(x) if (x == -1) {THROW(#x + " failed!");}

#define MAX_STR 255

class Joycon {

public:
	/* Constructor */
	Joycon(JOY_PID PID, wchar_t* serial_number);

	~Joycon();

	/* Connection Properties */
	JOY_PID PID;
	std::string name;
	std::string serial;
	wchar_t* serial_number;
	hid_device* handle;

	bool open();
	void close();

	SensorCalibration sensorCalib;

	bool alive = true;
	std::thread callback_thread;
	std::size_t package_number = 0;

	/* Joycon Data and Events */
	buttonData input;
	POWER battery;

	/* Event Management */
	std::queue<event*> e;
	void addEvent(buttonData change);
	event* getEvent();

	mutable std::mutex hid_mutex;

	InputBuffer send_command(unsigned char cmd, unsigned char subcmd, const ByteVector& data, bool blocking = true, Rumble rumble = Rumble());
	void capture();
	void callback();

	JoyconDeviceInfo request_device_info();

	// 0x00 - Used with cmd x11.Active polling for IR camera data. 0x31 data format must be set first
	// 0x01 - Same as 00
	// 0x02 - Same as 00. Active polling mode for IR camera data.For specific IR modes
	// 0x23 - MCU update state report ?
	// 0x30 - Standard full mode.Pushes current state @60Hz
	// 0x31 - NFC / IR mode. Pushes large packets @60Hz
	// 0x33 - Unknown mode.
	// 0x35 - Unknown mode.
	// 0x3F - Simple HID mode.Pushes updates with every button press
	// 31 input report has all zeroes for IR/NFC data if a 11 ouput report with subcmd 03 00 or 03 01 or 03 02 was not sent before.
	void set_input_report_mode(unsigned char irm);

	TriggerButtonElapsedTime trigger_button_elapsed_time();

	// x00 	Disconnect(sleep mode / page scan mode)
	// x01 	Reboot and Reconnect(page mode)
	// x02 	Reboot and enter Pair mode(discoverable)
	// x04 	Reboot and Reconnect(page mode / HOME mode ? )
	void set_HCI_state(unsigned char state);


	ByteVector SPI_flash_read(unsigned int address, unsigned char length);


	void set_player_lights(PLAYER_LIGHTS arg);

	PLAYER_LIGHTS get_player_lights();

	void set_home_light(const HOME_LIGHT& led_data);

	void enable_IMU(bool enable);

	// Sending x40 x01 (IMU enable), if it was previously disabled, resets your configuration to 0x03 0x00 0x01 0x01
	void set_IMU_sensitivity(unsigned char gyro_sens, unsigned char acc_sens, unsigned char gyro_perf_rate, unsigned char acc_aa_filter);

	void enable_vibration(bool enable);

	POWER get_regulated_voltage();

	void send_rumble(Rumble rumble = Rumble());

	SensorCalibration get_sensor_calibration();

	Color24 get_body_RGB();

	Color24 get_button_RGB();

	void check_input_arguments(std::unordered_set<unsigned char> list, unsigned char arg, std::string error_msg) const;
};
