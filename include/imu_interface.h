/*
 * imu_interface.h
 *
 *      Author: AritzElge
 */

#ifndef INCLUDE_IMU_INTERFACE_H_
#define INCLUDE_IMU_INTERFACE_H_

#include <stdbool.h>
#include <stdint.h>

// Structure for better efficiency
typedef struct {
    float f32_x;
    float f32_y;
    float f32_z;
} imu_axis_data_t;

// Function Types
/**
 * @brief Type definition for the IMU Start function pointer.
 * @return true if successful, false otherwise.
 */
typedef bool (*imu_start_t)(void);

/**
 * @brief Type definition for the Get Accelerometer Data function pointer.
 * @param[out] f_accel_x  pointer to acceleration data.
 * @param[out] f_accel_y  pointer to acceleration data.
 * @param[out] f_accel_z  pointer to acceleration data.
 * @return true if successful, false otherwise.
 */
typedef bool (*get_imu_accel_t)(float* f_accel_x, float* f_accel_y, float* f_accel_z);

/**
 * @brief Type definition for the Get Gyroscope Data function pointer.
 * @param[out] f_gyros_x pointer to Gyroscope data.
 * @param[out] f_gyros_y pointer to Gyroscope data.
 * @param[out] f_gyros_z pointer to Gyroscope data.
 * @return true if successful, false otherwise.
 */
typedef bool (*get_imu_gyros_t)(float* f_gyros_x, float* f_gyros_y, float* f_gyros_z);

/**
 * @brief Type definition for the Get Magnetomoter Data function pointer.
 * @param[out] f_magnet_x pointer to magnetometer data.
 * @param[out] f_magnet_y pointer to magnetometer data.
 * @param[out] f_magnet_z pointer to magnetometer data.
 * @return true if successful, false otherwise.
 */
typedef bool (*get_imu_mag_t)(float* f_magnet_x, float* f_magnet_y, float* f_magnet_z);

#ifdef __cplusplus
extern "C" {
#endif

// Pointer storing functions
/**
 * @brief Sets the specific hardware implementation for the accelerometer data retrieval.
 * @param[in] pfn_fptr The function pointer to the hardware driver.
 * @return true if registration is successful.
 */
bool set_imu_accelFunction(get_imu_accel_t pfn_fptr);

/**
 * @brief Sets the specific hardware implementation for the gyroscope data retrieval.
 * @param[in] pfn_fptr The function pointer to the hardware driver.
 * @return true if registration is successful.
 */
bool set_imu_gyrosFunction(get_imu_gyros_t pfn_fptr);

/**
 * @brief Sets the specific hardware implementation for the magnetomoter data retrieval.
 * @param[in] pfn_fptr The function pointer to the hardware driver.
 * @return true if registration is successful.
 */
bool set_imu_magFunction(get_imu_mag_t pfn_fptr);

// API Public functions
/**
 * @brief Configures and starts the IMU system using the registered start function.
 * @param[in] imu_start_function The initial start routine for the specific hardware.
 * @return true if configuration is successful.
 */
bool imu_config(imu_start imu_start_function);

/**
 * @brief Retrieves all IMU data (Accel, Gyros, Mag) using the registered hardware functions.
 * @param[out] f32_accelOX... Data output parameters.
 * @return true if all data retrieval is successful.
 */
bool get_imu_data(imu_axis_data_t* st_imu_accel_data,
				  imu_axis_data_t* st_imu_gyros_data,
				  imu_axis_data_t* st_imu_magnet_data);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_IMU_INTERFACE_H_ */