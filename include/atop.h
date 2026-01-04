#ifndef INCLUDE_ATOP_H_
#define INCLUDE_ATOP_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --- CALLBACK TYPES --- */

/**
 * @brief Function pointer type for hardware drivers.
 * 
 * This type allows the user to implement hardware-specific logic 
 * using basic types (float pointers). This abstracts the library's 
 * internal data structures from the user.
 * 
 * @param[out] pf32_x Pointer to store the X-axis value.
 * @param[out] pf32_y Pointer to store the Y-axis value.
 * @param[out] pf32_z Pointer to store the Z-axis value.
 * @return true if the hardware read was successful, false otherwise.
 */
typedef bool (*pfn_atop_get_raw_t)(float* pf32_x, float* pf32_y, float* pf32_z);

// IMU interface configuration funtion pointer typedefs:
typedef bool (*get_imu_accel_t)(float* f_accel_x, float* f_accel_y, float* f_accel_z);
typedef bool (*get_imu_gyros_t)(float* f_gyros_x, float* f_gyros_y, float* f_gyros_z);
typedef bool (*get_imu_mag_t)(float* f_magnet_x, float* f_magnet_y, float* f_magnet_z);

/* --- PUBLIC API --- */

/**
 * @brief Configures the ATOP library by injecting user-defined hardware drivers.
 * 
 * @param[in] pfn_accel Pointer to the accelerometer read function.
 * @param[in] pfn_gyro  Pointer to the gyroscope read function.
 * @param[in] pfn_mag   Pointer to the magnetometer read function.
 * @return true if all drivers were registered successfully.
 */
bool atop_imu_configure(get_imu_accel pfn_imuAccelFunction, 
                        get_imu_gyros pfn_imuGyrosFunction, 
                        get_imu_mag pfn_imuMagnetFunction);
                        
/**
 * @brief Starts the library execution loop.
 * 
 * This function triggers the internal sampling and processing logic.
 * Note: Depending on implementation, this might be a blocking call.
 * 
 * @return false if an unrecoverable error occurs.
 */
bool atop_start(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_ATOP_H_ */
