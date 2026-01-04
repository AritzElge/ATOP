#ifndef INCLUDE_ATOP_H_
#define INCLUDE_ATOP_H_

#include <stdbool.h>
#include "atop_types.h"

#ifdef __cplusplus
extern "C" {
#endif

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
