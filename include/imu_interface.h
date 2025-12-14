/*
 * imu_interface.h
 *
 *      Author: AritzElge
 */

#ifndef INCLUDE_IMU_INTERFACE_H_
#define INCLUDE_IMU_INTERFACE_H_

//#include <stddef.h>
#include <stdbool.h>

// Function Types
/**
 * @brief Type definition for the IMU Start function pointer.
 * @return true if successful, false otherwise.
 */
typedef bool (*imu_start)(void);

/**
 * @brief Type definition for the Get Accelerometer Data function pointer.
 * @param[out] accelOX X-axis acceleration.
 * @param[out] accelOY Y-axis acceleration.
 * @param[out] accelOZ Z-axis acceleration.
 * @return true if successful, false otherwise.
 */
typedef bool (*get_imu_accel)(float* accelOX, float* accelOY, float* accelOZ);

/**
 * @brief Type definition for the Get Gyroscope Data function pointer.
 * @param[out] accelOX X-axis acceleration.
 * @param[out] accelOY Y-axis acceleration.
 * @param[out] accelOZ Z-axis acceleration.
 * @return true if successful, false otherwise.
 */
typedef bool (*get_imu_gyros)(float* gyrosOX, float* gyrosOY, float* gyrosOZ);

/**
 * @brief Type definition for the Get Magnetomoter Data function pointer.
 * @param[out] accelOX X-axis acceleration.
 * @param[out] accelOY Y-axis acceleration.
 * @param[out] accelOZ Z-axis acceleration.
 * @return true if successful, false otherwise.
 */
typedef bool (*get_imu_mag)(float* magOX, float* magOY, float* magOZ);

#ifdef __cplusplus
extern "C" {
#endif

// Pointer storing functions
/**
 * @brief Sets the specific hardware implementation for the accelerometer data retrieval.
 * @param[in] fptr The function pointer to the hardware driver.
 * @return true if registration is successful.
 */
bool set_imu_accelFunction(get_imu_accel fptr);

/**
 * @brief Sets the specific hardware implementation for the gyroscope data retrieval.
 * @param[in] fptr The function pointer to the hardware driver.
 * @return true if registration is successful.
 */
bool set_imu_gyrosFunction(get_imu_gyros fptr);

/**
 * @brief Sets the specific hardware implementation for the magnetomoter data retrieval.
 * @param[in] fptr The function pointer to the hardware driver.
 * @return true if registration is successful.
 */
bool set_imu_magFunction(get_imu_mag fptr);

// API Public functions
/**
 * @brief Configures and starts the IMU system using the registered start function.
 * @param[in] imu_start_function The initial start routine for the specific hardware.
 * @return true if configuration is successful.
 */
bool imu_config(imu_start imu_start_function);

/**
 * @brief Retrieves all IMU data (Accel, Gyros, Mag) using the registered hardware functions.
 * @param[out] accelOX... Data output parameters.
 * @return true if all data retrieval is successful.
 */
bool get_imu_data(float* accelOX, float* accelOY, float* accelOZ,
					float* gyrosOX, float* gyrosOY, float* gyrosOZ,
					float* magOX, float* magOY, float* magOZ);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_IMU_INTERFACE_H_ */