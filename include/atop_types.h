#ifndef ATOP_TYPES_H_
#define ATOP_TYPES_H_

#include <stdbool.h>

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

#endif