#include <stdbool.h>
#include "atop.h"
#include "imu_interface.h"

static imu_axis_data_t st_accel_data;
static imu_axis_data_t st_gyros_data;
static imu_axis_data_t st_magnet_data;

/**
 * @brief Library IMU configuration
 * @param[in] pfn_imuAccelFunction The function pointer to the hardware driver for acceleration data adquisition.
 * @param[in] pfn_imuGyrosFunction The function pointer to the hardware driver for gyroscope data adquisition.
 * @param[in] pfn_imuMagnetFunction The function pointer to the hardware driver for magnetometer data adquisition.
 * @return true if configuration is successful.
 */
bool atop_imu_configure(get_imu_accel_t pfn_imuAccelFunction, get_imu_gyros_t pfn_imuGyrosFunction, get_imu_mag_t pfn_imuMagnetFunction)
{
    // Variable initialization
    bool ret_val = true;

    //Set IMU data getter functions for imu_interface:
    ret_val = ret_val && set_imu_accelFunction(pfn_imuAccelFunction);
    ret_val = ret_val && set_imu_gyrosFunction(pfn_imuGyrosFunction);
    ret_val = ret_val && set_imu_magFunction(pfn_imuMagnetFunction);

    return ret_val;
}

/**
 * @brief Main Library Logic
 * @return fakse if an error happened.
 */
bool atop_start(void)
{
    // Variable initialization
    bool ret_val = true;

    while(ret_val)
    {
        // Get IMU data
        ret_val = get_imu_data(&st_accel_data,
                               &st_gyros_data,
                               &st_magnet_data);
        (void)sleep(1U); 
    } 
    return false;
}
