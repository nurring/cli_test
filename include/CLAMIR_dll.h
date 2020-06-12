/*
*	Copyright(C) 2019 New Infrared Technologies
*
*	Permission is hereby granted, free of charge, to any person buying or acquiring a copy of this software and associated documentation files(the ‘Software’) from New Infrared Technologies, to deal in the Software without limitation the rights to use, copy, merge, publish, distribute, sublicense, and/or sell copies of the Software, subject to the following conditions :
*
*	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED ‘AS IS’, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/



/** \file CLAMIR_dll.h
*	Description file of the CLAMIR communication DLL. This DLL allows the user to communicate with a New Infrared Technologies CLAMIR system and configurate its parameters to perform with success its control and monitorization processes.
*	Due the fast and simple communication protocol of the CLAMIR system some cautions must be taken when using this DLL to configure it. The values paired in MAX/MIN limits should be changed by the user with caution to prevent setting a maximum value lower than its minimum counterpart.
*	A misconfiguration of those parameters could lead to undesired and unexpected control and monitorization results and potentially damage the CLAMIR system. 
*/

#pragma once
#include <stdint.h>
#include <winsock.h>

#ifdef CLAMIRDLL_EXPORTS
#define CLAMIRDLL_API __declspec(dllexport)
#else
#define CLAMIRDLL_API __declspec(dllimport)
#endif


	/*!
	 @brief The ConnectCLAMIR function initializes sockets and establishes connections for commands and images

	 @param aIPAddress Pointer to the IP address buffer w to connect to CLAMIR
	 @returns 0 if connections are stablished ok
	 @returns returns -1 if failed to assign a socket
	 @returns returns -2 if failed to connect
	*/

	extern "C" CLAMIRDLL_API int ConnectCLAMIR(char *aIPaddress);
	
	/**
	 @brief The DiscconnectCLAMIR function drops the connection freeing the DLL sockets for further uses.

	 @returns 0 if disconnection is successful
	 @returns returns -1 if failed to close connections
	 @returns returns -2 if failed to close sockets
	 */
	extern "C" CLAMIRDLL_API int DisconnectCLAMIR();


	/**
	@brief Checks the status of the connection.

	@returns 1 if the communication with a CLAMIR system is active, 0 otherwise
	*/	
	extern "C" CLAMIRDLL_API int IsConnected();

		/**
		* @struct ImageHeader
		* @brief Image metadata associated with each image
		* @param Power Power in watts of CLAMIR system output
		* @param MeltPoolArea Number of pixels above the treshold
		* @param Width Width of the melt pool in mm
		* @param RefWidth Width of reference in mm
		* @param TrackNum Current track of the process
		* @param FrameMax Maximum pixel value of the image
		* @param FrameNum ID number of the current frame
		* @param IODigitalPortStatus Bits 0 In1, 1 In2, 2 Out1 (alarm), 3 Out2, 4 In3, 5 In4, 6 Out3, 7 Out4
		* @param LaserStatus Byte that indicates if a laser detection is happening (1) or not (0)
		* @param StateMachine Byte with the machine state of CLAMIR: 0x00 Manual control, 0x08 Idle, 0x09 Set point, 0x0A Control, 0x0B Preheating
		* @param Temperature Internal CLAMIR temperature in degrees celsius
		*/
		extern "C" CLAMIRDLL_API struct ImageHeader
		{
			int Power, MeltPoolArea, TrackNum, FrameMax, FrameNum;
			float Width, RefWidth, Temperature;
			char LaserStatus, StateMachine;
			int16_t IODigitalPortStatus;
		};
		

		/**
		@brief The function GetImage reads an image and its header information from CLAMIR system
		@param aImageHeader Pointer to an ImageHeader structure
		@param aImage Pointer to an array of 4096 int16_t pixels
		@returns 0 if data was successfully retrieved
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on a closed connection
		*/
		extern "C" CLAMIRDLL_API int GetImage(ImageHeader *aImageHeader, int16_t *aImage);

		/**
		@brief The function GetImageRawHeader reads an image and its raw header information from CLAMIR system.
		Equivalent to the image and its header data acquired from CLAMIR system in NIT .dat files
		@param rawHeader Pointer to a buffer of raw header data. 60 bytes integer array.
		@param aImage Pointer to an array of 4096 int16_t pixels
		@returns 0 if data was successfully retrieved
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on a closed connection
		*/
		extern "C" CLAMIRDLL_API int GetImageRawHeader(int *rawHeader, int16_t *aImage);


		/**
		@brief The KISet function sends to the CLAMIR system a new KI value to set the PID control

		*This function allows the user to change the integral term of the PID control system.

		*- Default value: 500

		*- Bounds
		*	- Max value 30000
		*	- Min value 0

		@param Data Variable with the value of the new KI
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int KISet(int16_t data);

		/**
		@brief The KIGet function gets the KI value of a CLAMIR system
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int KIGet(int16_t *data);

		/**
		@brief The KPSet function sends to the CLAMIR system a new KP value to set the PID control

		*This function allows the user to change the proportional term of the PID control system.

		*- Default value: 200

		*- Bounds
		*	- Max value 30000
		*	- Min value 0

		@param Data Variable with the value of the new KP
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int KPSet(int16_t data);

		/**
		@brief The KPGet function gets the KP value of a CLAMIR system
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int KPGet(int16_t *data);

		/**
		@brief The KDSet function sends to the CLAMIR system a new KD value to set the PID control

		*This function allows the user to change the derivative term of the PID control system.

		*- Default value: 100

		*- Bounds
		*	- Max value: 30000
		*	- Min value: 0

		@param Data Variable with the value of the new KD
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int KDSet(int16_t data);

		/**
		@brief The KDGet function gets the KD value of a CLAMIR system
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int KDGet(int16_t *data);

		/**
		@brief The MaxPowerSet function sets the maximum power in watts.
		
		*The maximum power is associated to the 10 volt limit of the CLAMIR analog output. This range is recalculated when <b>Max power</b> or <b>Min power</b> are changed.

		*- Default value: 1500 watts

		*- Bounds
		*	- Max value: 30000 watts
		*	- Min value: 100 watts

		@param Data Variable with the value of the new maximum power
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int MaxPowerSet(int16_t data);

		/**
		@brief The MaxPowerGet function reads the maximum power in watts
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int MaxPowerGet(int16_t *data);

		/**
		@brief The MinPowerSer function sets the minimum power in watts

		*The minimum power is associated to the 0 volt limit of the CLAMIR analog output. This range is recalculated when <b>Max power</b> or <b>Min power</b> are changed.

		*- Default value: 500 watts

		*- Bounds
		*	- Max value: 9900 watts
		*	- Min value: -30000 watts

		@param Data Variable with the value of the new minimum power
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int MinPowerSet(int16_t data);

		/**
		@brief The MinPowerGet function reads the minimum power in watts
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int MinPowerGet(int16_t *data);

		/**
		@brief The ThresholdSet function sets the threshold value in digital counts for melt pool discrimination

		*Pixels with signal values above this threshold are used in the measurements of the melt pool geometry and in the autodetection of a laser or process activation. Pixels below this value are considered as background.

		*- Default value: 1200 digital counts of signal by the CLAMIR sensor

		*- Bounds
		*	- Max value 5000 digital counts
		*	- Min value 0 digital counts

		@param Data Variable with the value of the threshold
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int ThresholdSet(int16_t data);

		/**
		@brief The ThresholdGet function reads the threshold value
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ThresholdGet(int16_t *data);

		/**
		@brief The ThresholdToStartTracksSet function sets the threshold of the melt pool area that will start a laser detection

		*This command selects the number of pixels of the image that should be above the set signal intensity threshold to start the measuring process and consider a laser to be detected from a laser off detection. Only used with the external laser detection disabled.

		*- Default value: 40 pixels

		*- Bounds
		*	- Max value 2000 pixels
		*	- Min value 0 pixels

		@param Data Variable with the value of the new threshold to evaluate the area
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/

		extern "C" CLAMIRDLL_API int ThresholdToStartTracksSet(int16_t data);

		/**
		@brief The ThresholdToStartTracksGet function reads the threshold of the melt pool area that will start a laser detection
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ThresholdToStartTracksGet(int16_t *data);

		/**
		@brief The ThresholdToEndTracksSet function sets the threshold of the melt pool area that will stop a laser detection

		*Number of pixels above the intensity threshold, below laser will be considered as not detected. Only used with the external laser detection disabled.

		*- Default value: 30 pixels

		*- Bounds
		*	- Max value 1000 pixels
		*	- Min value 0 pixels

		@param Data Variable with the value of the new minimum power
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int ThresholdToEndTracksSet(int16_t data);

		/**
		@brief The ThresholdToEndTracksGet function reads the threshold of the melt pool area that will stop a laser detection
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ThresholdToEndTracksGet(int16_t *data);

		/**
		@brief The ManualPowerSet function writes the power in watts that CLAMIR will use in manual mode and in setpoint calculation

		*Sets the power in watts that CLAMIR will use in manual mode or when in SET_POINT calculation state.

		*- Default value: 1000 watts

		*- Bounds
		*	- Max value 30000 watts
		*	- Min value 0 watts

		@param Data Variable with the value of the new power
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int ManualPowerSet(int16_t data);

		/**
		@brief The ManualPowerGet function reads the manual power of a CLAMIR system
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ManualPowerGet(int16_t *data);

		/**
		@brief The AutoCalibrateSet function starts an autocalibration process that will close the shutter, acquire a background image to subtract to the images, and open the shutter again
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AutoCalibrateSet();

		/**
		@brief The ModeSet function sets the control mode of the CLAMIR system

		*Sets the mode of operation of CLAMIR. 
		*- Manual mode sets a constant power and does not count tracks. Integer identifier 2.
		*- Continuous mode performs control for a continuous process. Integer identifier 0.
		*- Tracks mode performs control for processes with several laser power off and on.

		*- Default value: 2 (Manual mode)

		*- Bounds
		*	- Max value 2
		*	- Min value 0 

		@param Data Variable with the value of the new control mode, 0 being continuous, 1 being tracks and 2 being manual
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int ModeSet(int16_t data);

		/**
		@brief The ModeGet function gets the control mode of a CLAMIR system
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ModeGet(int16_t *data);

		/**
		@brief The ReferenceTrackStart function writes the start track of the reference width measurement

		*Sets the first track from which the system will calculate the reference width set point until the ReferenceTrackEnd is reached. Previous tracks will be ignored.

		*- Default value: 0

		*- Bounds
		*	- Max value 100
		*	- Min value 0

		@param Data Variable with the value of the new start track for reference width measurement
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int ReferenceTrackStartSet(int16_t data);

		/**
		@brief The ReferenceTrackStartGet function gets the start track of the reference width measurement
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ReferenceTrackStartGet(int16_t *data);

		/**
		@brief The ReferenceTrackEndSet function sets the end track of the reference width measurement

		*This command configures the track until which the system will calculate a set point of reference width. On the previous tracks the system will set the constant power set by Manual Power and use the measurements to calculate a reference width. After this track ends the system will use the measurements to control the analog output.

		*- Default value: 3 

		*- Bounds
		*	- Max value 100
		*	- Min value 0

		@param Data Variable with the value of the new end track for reference width measurement
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int ReferenceTrackEndSet(int16_t data);

		/**
		@brief The ReferenceTrackEndGet function gets the end track of the reference width measurement
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ReferenceTrackEndGet(int16_t *data);

		/**
		@brief The TrackDurationSet function writes the duration in seconds of a track when in continuous control mode.

		*- Default value: 2 seconds

		*- Bounds
		*	- Max value 1000 seconds
		*	- Min value 0.1 seconds

		@param Data Variable with the value of the new track duration in seconds
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int TrackDurationSet(float data);

		/**
		@brief The TrackDurationGet function reads the duration in seconds of a track when in continuous control mode
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int TrackDurationGet(float *data);

		/**
		@brief The ManualReferenceWidthValueSet function sets the manual reference width in millimeters by the user.

		*Sets a manual width of reference as width of reference, but CLAMIR does not use it until the function <b>ForceManualReferenceWidthSet()</b> is used.

		*- Default value: 1 mm

		*- Bounds
		*	- Max value 65 mm
		*	- Min value 0 mm

		@param Data Variable with the value of the manual reference width
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int ManualReferenceWidthValueSet(float data);

		/**
		@brief The ManualReferenceWidth function gets the current manual reference width in millimeters
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ManualReferenceWidthValueGet(float *data);

		/**
		@brief The UpdateSetPointSet function updates the setpoint width with the manual reference width
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int UpdateSetPointSet();

		/**
		@brief The RoundROISet function sets the rounding mode of the region of interest over the CLAMIR image

		*This command configures the rounding of the Region of Interest (ROI). A value of 0 is used to deactivate the rounding function. A value of 1 indicates a minimum rounding, value of 2 is used for a medium rounding and value of 3 is used for the maximum rounding of the ROI.

		*- Default value: 0 (no rounding)

		*- Bounds
		*	- Max value 3
		*	- Min value 0

		@param Data Variable with the value of the new ROI, 0 being not rounding, 1 minimum rounding, 2 medium rounding and 3 max rounding
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int RoundROISet(int16_t data);

		/**
		@brief The RoundingROIGet function gets the rounding of the region of interest
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int RoundROIGet(int16_t *data);

		/**
		@brief The EnableROISet function enables or disables the application of a region of interest over the CLAMIR image

		*If activated, values outside of the ROI will not be taken in consideration on the measurements. If rounding is active, the vertices of the squared ROI will also be nullified depending on the size and rounding mode of the ROI.

		*- Default value: 0 (disabled)

		*- Bounds
		*	- Max value 1 (enabled)
		*	- Min value 0 (disabled)

		@param Data Variable to set the ROI enabled or disabled
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int EnableROISet(int data);

		/**
		@brief The EnableROIGet function reads the enabled status of the ROI
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int EnableROIGet(int *data);

		/**
		@brief The ROICoordinatesSet function writes the coordinates of the points that define the region of interest

		*Set the coordinates of the ROI using the coordinates of the lowest and highest pixels of the ROI. The coordinates X1 and Y1 should always be lower than the coordinates X2 and Y2 respectively. 

		*- Default value: (X1, Y1) = (2, 2) --- (X2, Y2) = (61, 61)

		*- Bounds
		*	- X1 and Y1 max value 62
		*	- X1 and Y1 min value 1
		*	- X2 and Y2 max value 63
		*	- X2 and Y2 min value 2

		@param X1 Variable with the lowest X coordinate of the ROI
		@param Y1 Variable with the lowest Y coordinate of the ROI
		@param X2 Variable with the highest X coordinate of the ROI
		@param Y2 Variable with the highest Y coordinate of the ROI
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		@returns -4 on X1 or Y1 being equal or higher than X2 or Y2
		*/
		extern "C" CLAMIRDLL_API int ROICoordinatesSet(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2);

		/**
		@brief The ROICoordinatesGet function read the coordinates of the points that define the region of interest
		@param X1 Pointer where the function will store the lowest X coordinate fo the ROI
		@param Y1 Pointer where the function will store the lowest Y coordinate fo the ROI
		@param X2 Pointer where the function will store the highest X coordinate fo the ROI
		@param Y2 Pointer where the function will store the highest Y coordinate fo the ROI
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ROICoordinatesGet(int16_t *X1, int16_t *Y1, int16_t *X2, int16_t *Y2);

		/**
		@brief ThePowerLimitMaxSet function sets the maximum limit of the power in watts the CLAMIR system will be able to set

		*Sets the minimum output power for a process.

		*- Default value: 1500 watts

		*- Bounds
		*	- Max value 30000 watts
		*	- Min value 1 watt

		@param Data Variable with the value of the new maximum power limit
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int PowerLimitMaxSet(int16_t data);

		/**
		@brief The PowerLimitMaxGet function gets the maximum power limit in watts
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int PowerLimitMaxGet(int16_t *data);

		/**
		@brief The PowerLimitMinSet function sets the minimum limit of the power in watts the CLAMIR system will be able to set

		*Sets the minimum power limit for a process.

		*- Default value: 500 watts

		*- Bounds
		*	- Max value 9999 watts
		*	- Min value 0 watt

		@param Data Variable with the value of the new minimum power limit
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int PowerLimitMinSet(int16_t data);

		/**
		@brief The PowerLimitMinGet function gets the minimum power limit in watts
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int PowerLimitMinGet(int16_t *data);

		/**
		@brief The PixelToMillimeterRatioSet function writes the ratio of how many millimeters are in each pixel, with a precision of micrometers

		*Sets the ratio of conversion between width measured in pixels to millimeters.

		*- Default value: 0,015 millimeter per pixel

		*- Bounds
		*	- Max value 10 millimeters per pixel
		*	- Min value 0,01 millimeter per pixel

		@param Data Variable with the value of the new pixel to millimeter ratio
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int PixelToMillimeterRatioSet(float data);

		/**
		@brief The PixelToMillimeterRatioGet function reads the pixel to millimeter ratio of CLAMIR
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int PixelToMillimeterRatioGet(float *data);

		/**
		@brief The EndOfProcessTimeSet function writes the time in milliseconds of consecutive images without laser detection to consider a process finished

		*Sets the time in milliseconds that the laser should be off to consider an end of a process. If the mode of the CLAMIR system is set to tracks, this time should be greater than the laser off time between tracks. 

		*- Default value: 5000 milliseconds

		*- Bounds
		*	- Max value 30000 milliseconds
		*	- Min value 500 milliseconds

		@param Data Variable with the value of the end of process time
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int EndOfProcessTimeSet(int16_t data);

		/**
		@brief The EndOfProcessTimeGet function reads the end of process time in milliseconds
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int EndOfProcessTimeGet(int16_t *data);

		/**
		@brief The LimitIntegralSet function sets the limit of integral correction of the PID controller

		*Sets the limit in watts that the integral branch of the PID could reach.

		*- Default value: 5000 watts

		*- Bounds
		*	- Max value 10000 watts
		*	- Min value 0 watts

		@param Data Variable with the value of integral limit
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int LimitIntegralSet(int16_t data);

		/**
		@brief The LimitIntegralGet function gets the limit of integral correction of the PID controller
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int LimitIntegralGet(int16_t *data);

		/**
		@brief The LimitSlewRateSet function sets the limit of the slew rate in W/ms

		*This command sets the maximum slew rate in watts per millisecond

		*- Default value: 1 W/ms

		*- Bounds
		*	- Max value 300 W/ms
		*	- Min value 0.01 W/ms

		@param Data Variable with the value of the slew rate limit
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int LimitSlewRateSet(float data);

		/**
		@brief The LimitSlewRateGet function gets the limit of the slew rate
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int LimitSlewRateGet(float *data);

		/**
		@brief The CircularBufferSizeSet function writes the size of the circular buffer that holds the measured widths that will be used to calculate the power output

		*CLAMIR uses a circular buffer to average the latest width measurements to be used in PID control. This command sets the amount of values stored and used to perform the mean calculation. Greater values average more samples.

		*- Default value: 4

		*- Bounds
		*	- Max value 512
		*	- Min value 1

		@param Data Variable with the size value of the circular buffer
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int CircularBufferSizeSet(int16_t data);

		/**
		@brief The LimitCircularBufferSizeGet function reads the size of the circular buffer
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int CircularBufferSizeGet(int16_t *data);

		/**
		@brief The EnableAlarmSet function enables or disables the alarm functionality of the CLAMIR system

		*- Default value: 0 (disabled)

		*- Bounds
		*	- Max value 1 (enabled)
		*	- Min value 0 (disabled)

		@param Data Variable with the flag to enable or disable the alarm
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int EnableAlarmSet(int data);

		/**
		@brief The EnableAlarmGet function gets the enabled state of the alarm
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int EnableAlarmGet(int *data);

		/**
		@brief The AlarmMaxSet function writes the maximum limit that would set on the alarm, in millimeters with a precision of two digits

		*This command sets the upper limit above an alarm will be activated.

		*- Default value: 5 mm

		*- Bounds
		*	- Max value 320 mm
		*	- Min value 0 mm

		@param Data Variable with the value of the maximum limit of the alarm
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int AlarmMaxSet(float data);

		/**
		@brief The AlarmMaxGet function reads the maximum limit that would set on the alarm, in millimeters with a precision of two digits
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AlarmMaxGet(float *data);

		/**
		@brief The AlarmMinSet function writes the minimum limit that would set on the alarm, in millimeters with a precision of two digits

		*This command sets the lower limit below an alarm will be activated.

		*- Default value: 1 mm

		*- Bounds
		*	- Max value 320 mm
		*	- Min value 0 mm

		@param Data Variable with the value minimum limit of the alarm
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int AlarmMinSet(float data);

		/**
		@brief The AlarmMinGet function reads the minimum limit that would set on the alarm, in millimeters with a precision of two digits
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AlarmMinGet(float *data);

		/**
		@brief The AlarmTimeSet function sets the time in milliseconds the calculated width must be outside the set bounds to set on the alarm

		*This command sets the time in milliseconds that the width measurement can be outside of the alarm boundaries before activating the alarm.

		*- Default value: 2000 milliseconds

		*- Bounds
		*	- Max value 10000 milliseconds
		*	- Min value 0 milliseconds

		@param Data Variable with the value of the alarm time
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int AlarmTimeSet(int16_t data);

		/**
		@brief The AlarmTimeGet function gets the time in milliseconds the calculated width must be outside the set bounds to set on the alarm
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AlarmTimeGet(int16_t *data);

		/**
		@brief The SerialNumberGet function reads the Serial Number of the CLAMIR system
		@param Data Pointer where the function will store the received value of 7 characters
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int SerialNumberGet(char *data);
		/**
		@brief The AutomeasureSet function enables or disables the auto measure function of CLAMIR

		*This command configures the mode in which the width of reference will be calculated. If enabled, CLAMIR will perform during the tracks of SET POINT state a calculation of this reference with the measured widths. If disabled, CLAMIR will use as reference width the latest reference width, being this reference the calculated in the latest process or a reference width set manually by the user.

		*- Default value: 1 (enabled)

		*- Bounds
		*	- Max value 1 (enabled)
		*	- Min value 0 (disabled)

		@param Data Variable with the flag to enable or disable the auto measure function
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int AutomeasureSet(int data);

		/**
		@brief The AutomeasureGet function gets if CLAMIR has the auto measure functionality enabled
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AutomeasureGet(int *data);

		/**
		@brief The AutoShutterConfigurationSet function sets the configuration of the auto shutter process

		*The four parameters allow CLAMIR to perform calibrations by performing an autoshutter process. The parameter flagEnableInProcess allows the calibration process to be enabled only if a process is not currently running to not disturb the measurements or to do be enabled also during a process, in case for example of high variation of signal or very long processes.
		*There are two possible modes to launch an autoshutter process, timed events or drift temperature events. The two modes are exclusive between them, so only one of them can be enabled.

		*- Default value: by default, the auto shutter process and the auto shutter while in process flag are disabled. The active mode by default is the drift temperature one.

		*- Bounds
		*	- Max value 1 (enabled)
		*	- Min value 0 (disabled)

		@param flagEnable Variable to enable or disable the auto shutter function.
		@param flagEnableInProcess Variable to enable the auto shutter while a process is running.
		@param flagTemperaturDrift Variable to set the temperature drift activation of the auto shutter. Its excluding with flagTimer.
		@param flagTimer Variable to set the timer activation of the auto shutter. Its excluding with flagTemperaturDrift.
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 if both temperature drift and timer flags are ture or both are false
		*/
		extern "C" CLAMIRDLL_API int AutoShutterConfigurationSet(int flagEnable, int flagEnableInProcess, int flagTemperatureDrift, int flagTimer);

		/**
		@brief The AutoShutterConfigurationGet function gets the configuration of the auto shutter
		@param flagEnable Pointer where the function will store the enabled flag.
		@param flagEnableInProcess Pointer where the function will store the enabled while in process flag
		@param flagTemperaturDrift Pointer where the function will store the drift temperature flag
		@param flagTimer Pointer where the function will store the timer flag
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AutoShutterConfigurationGet(int *flagEnable, int *flagEnableInProcess, int *flagTemperatureDrift, int *flagTimer);

		/**
		@brief The AutoshutterDriftTemperatureSet function writes the temperature change in degrees Celsius that will set an auto shutter event

		*This value is the difference in degrees Celsius between the temperature when the last auto shutter was performed and the new temperature to launch an auto shutter event.

		*- Default value: 3 degrees Celsius

		*- Bounds
		*	- Max value 50 degrees Celsius
		*	- Min value 0.1 degrees Celsius

		@param Data Variable with the value of the temperature change
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int AutoshutterDriftTemperatureSet(float data);

		/**
		@brief The AutoshutterDriftTemperatureGet function reads the temperature change in degrees Celsius that will set an auto shutter event
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AutoshutterDriftTemperatureGet(float *data);

		/**
		@brief The AutoshutterTimerSet function writes the time in seconds that will set an auto shutter event

		*This value sets the time in seconds between auto shutter events if the timer mode for the auto shutter is active.

		*- Default value: 180 seconds

		*- Bounds
		*	- Max value 320000 seconds
		*	- Min value 10 seconds

		@param Data Variable with the value of the auto shutter time
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int AutoshutterTimerSet(float data);

		/**
		@brief The AutoshutterTimerGet function reads the time in seconds that will set an auto shutter event
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int AutoshutterTimerGet(float *data);

		/**
		@brief The LaserExternalSet function sets if the laser detection is taken from an external source on one of the digital input ports

		*This command configures the mode of detecting if a laser is active. If disabled, CLAMIR will perform a detection based in the signal detected by the sensor and the configured parameters of CLAMIR. If enabled, CLAMIR will consider to be a laser active by the signal supplied by the user in the Digital Input 1 pin.

		*- Default value: 0 (disabled)

		*- Bounds
		*	- Max value 1 (enabled)
		*	- Min value 0 (disabled)

		@param Data Variable with the flag to enable the external laser detection
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int LaserExternalSet(int data);

		/**
		@brief The LaserExternalGet function gets if the laser detection is taken from an external source on one of the digital input ports
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int LaserExternalGet(int *data);

		/**
		@brief The LaserONDelaySet function sets the number of frames to wait when the laser detection changes states from not detection to detection before calculating again the power output

		*This parameter allows the user to configure a delay in milliseconds between the detection of a laser ON from a laser OFF detection, before start performing a calculation of the controlled power.
		*In tracks processes if the OFF-ON transition is not instantaneous an overshoot correction may be performed. A small delay allows those anomalous measurements to be ignored so the correction overshoot is inexistent or mitigated.

		*- Default value: 0 milliseconds

		*- Bounds
		*	- Max value 1000 milliseconds
		*	- Min value 0 milliseconds

		@param Data Variable with the value of LaserOnDelay
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int LaserONDelaySet(int16_t data);

		/**
		@brief The LaserONDelayGet function gets the number of frames to wait when the laser detection changes states from not detection to detection
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int LaserONDelayGet(int16_t *data);

		/**
		@brief The EnablePreheatingSet function enables or disables the preheating mode

		*If enabled, at the start of a process CLAMIR will set the preheating power instead of the manual power for the configured preheating time.

		*- Default value: 0 (disabled)

		*- Bounds
		*	- Max value 1 (enabled)
		*	- Min value 0 (disabled)

		@param Data Variable with the flag to enable the preheating mode
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int EnablePreheatingSet(int data);

		/**
		@brief The EnablePreheatingGet function gets if the preheating mode is active
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int EnablePreheatingGet(int *data);

		/**
		@brief The PreheatingTimeSet function to writes in milliseconds the time CLAMIR will work in preheating mode when a process starts

		*This parameter is the time in milliseconds CLAMIR will stay in preheating mode at the start of a process.

		*- Default value: 0 milliseconds

		*- Bounds
		*	- Max value 30000 milliseconds
		*	- Min value 0 milliseconds

		@param Data Variable with the value of preheating time
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int PreheatingTimeSet(int16_t data);

		/**
		@brief The PreheatingTimeGet function reads in milliseconds the time CLAMIR will work in preheating mode when a process starts
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int PreheatingTimeGet(int16_t *data);

		/**
		@brief The PreheatingPowerSet function writes the power in watts that a CLAMIR system will output when in preheating mode

		*This parameter is the power in watts the CLAMIR system will set as analog output during the preheating time. Its purpose is to give the user the option to configure a different power than the manual power during the first instants of the process.

		*- Default value: 1500 watts

		*- Bounds
		*	- Max value 10000 watts
		*	- Min value 0 watts

		@param Data Variable with the value of preheating power
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int PreheatingPowerSet(int16_t data);

		/**
		@brief The PreheatingPowerGet function reads the power in watts that a CLAMIR system will output when in preheating mode
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int PreheatingPowerGet(int16_t *data);

		/**
		@brief The DigitalOut1Set function sets the digital value of the Digital Out 1 port of CLAMIR
		@param Data Variable with the flag to set the value of the CLAMIR digital port
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalOut1Set(int data);

		/**
		@brief The DigitalIn1Get function gets the value of the Digital In 1 port of CLAMIR
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalIn1Get(int *data);

		/**
		@brief The DigitalOut2Set function sets the digital value of the Digital Out 2 port of CLAMIR
		@param Data Variable with the flag to set the value of the CLAMIR digital port
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalOut2Set(int data);

		/**
		@brief The DigitalIn2Get function gets the value of the Digital In 2 port of CLAMIR
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalIn2Get(int *data);

		/**
		@brief The DigitalOut3Set function sets the digital value of the Digital Out 3 port of CLAMIR
		@param Data Variable with the flag to set the value of the CLAMIR digital port
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalOut3Set(int data);

		/**
		@brief The DigitalIn3Get function gets the digital value of the Digital In 3 port of CLAMIR
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalIn3Get(int *data);

		/**
		@brief The DigitalOut4Set function sets the digital value of the Digital Out 4 port of CLAMIR
		@param Data Variable with the flag to set the value of the CLAMIR digital port
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalOut4Set(int data);

		/**
		@brief The DigitalIn4Get function gets the value of the Digital In 4 port of CLAMIR
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int DigitalIn4Get(int *data);

		/**
		@brief The IntegrationTimeSet function sets the integration time in microseconds of the CLAMIR sensor electronics.

		*- Default value: 200 microseconds

		*- Bounds
		*	- Max value 800 microseconds
		*	- Min value 50 microseconds

		@param Data Variable with the value of the integration time
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int IntegrationTimeSet(int16_t data);

		/**
		@brief The IntegrationTimeGet function gets the integration time in microseconds of the CLAMIR sensor
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int IntegrationTimeGet(int16_t *data);

		/**
		*@brief The BiasVoltageSet function sets the Bias voltage in volts of the CLAMIR sensor.
		
		*Bias voltage is a gain control of the detector, higher bias voltage produce higher gain, but noisier sensor measurements.

		*- Default value: 2.00 volts

		*- Bounds
		*	- Max value 3.00 volts
		*	- Min value 1.00 volts

		@param Data Variable with the value of the bias voltage in volts with 1/2^14 precision and bounds of between 1 and 3 volts. 
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int BiasVoltageSet(float data);

		/**
		@brief The BiasVoltageGet function gets the bias voltage of the CLAMIR sensor
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int BiasVoltageGet(float *data);

		/**
		@brief The ShutterPositionSet function sets the position of CLAMIR shutter, a 1 value means closed, and a 0 value means open
		@param Data Variable with the flag to set the position of the CLAMIR shutter
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int ShutterPositionSet(int data);

		/**
		@brief The SaveEmbeddedConfigurationSet function sends CLAMIR the command to save the current configuration parameters in memory. On new starts of the CLAMIR system, it will launch with this configuration.
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int SaveEmbeddedConfigurationSet();

		/**
		@brief The BlackLevelSet function writes the black level of the CLAMIR system

		*Black level added to the acquired signal of the sensor in digital counts.

		*- Default value: 1000 digital counts

		*- Bounds
		*	- Max value 10000 digital counts
		*	- Min value 0 digital counts

		@param Data Variable with the value of the black level
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		@returns -3 on an out of bounds value
		*/
		extern "C" CLAMIRDLL_API int BlackLevelSet(int16_t data);

		/**
		@brief The BlackLevelGet function reads the black level of the CLAMIR system
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int BlackLevelGet(int16_t *data);

		/**
		@brief The EmbeddedSWVersion function reads the embedded software version of the CLAMIR system
		@param Data Pointer where the function will store the received value
		@returns 0 on a successful communication
		@returns -1 on a timeout error
		@returns -2 on another communication error
		*/
		extern "C" CLAMIRDLL_API int EmbeddedSWVersion(int16_t *data);