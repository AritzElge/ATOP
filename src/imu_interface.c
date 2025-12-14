/*
 * imu_interface.c
 *
 *      Author: AritzElge
 */
#include <stdbool.h>
#include "imu_interface.h"
// Function Pointer variables:
static get_imu_accel stored_get_imu_accel = NULL;
static get_imu_gyros stored_get_imu_gyros = NULL;
static get_imu_mag stored_get_imu_mag = NULL;

bool set_imu_accelFunction(get_imu_accel fptr)
{
	bool ret_val = true;

    if (fptr == NULL)
    {
        ret_val = false;
    }
    else
    {
        stored_get_imu_accel = fptr;
        // Redundant Check for hardware/memory failure
        if (stored_get_imu_accel != fptr)
        {
            ret_val = false;
        }
    }
	return ret_val;
}

bool set_imu_gyrosFunction(get_imu_gyros fptr)
{
	bool ret_val = true;

    if (fptr == NULL)
    {
        ret_val = false;
    }
    else
    {
	    stored_get_imu_gyros = fptr;
        // Redundant Check for hardware/memory failure
	    if (stored_get_imu_gyros != fptr)
        {
            ret_val = false;
        }
    }
	return ret_val;
}

bool set_imu_magFunction(get_imu_mag fptr)
{
	bool ret_val = true;

    if (fptr == NULL)
    {
        ret_val = false;
    }
    else
    {
	    stored_get_imu_mag = fptr;
        // Redundant Check for hardware/memory failure
	    if (stored_get_imu_mag != fptr)
        {
            ret_val = false;
        }
    }
	return ret_val;
}

bool imu_config(imu_start imu_start_function)
{
	return imu_start_function();
}

bool get_imu_data(float* accelOX, float* accelOY, float* accelOZ,
					float* gyrosOX, float* gyrosOY, float* gyrosOZ,
					float* magOX, float* magOY, float* magOZ)
{
	bool ret_val = true;
	if (stored_get_imu_accel != NULL)
    {
		ret_val = ret_val && stored_get_imu_accel(accelOX, accelOY, accelOZ);
	}
    else
    {
		ret_val = ret_val && false;
	}
	if (stored_get_imu_gyros != NULL)
    {
		ret_val = ret_val && stored_get_imu_gyros(gyrosOX, gyrosOY, gyrosOZ);
	}
    else
    {
		ret_val = ret_val && false;
	}
	if (stored_get_imu_mag != NULL)
    {
		ret_val = ret_val && stored_get_imu_mag(magOX, magOY, magOZ);
	}
    else
    {
		ret_val = ret_val && false;
	}

	return ret_val;
}