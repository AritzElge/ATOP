/*
 * imu_interface.c
 *
 *      Author: AritzElge
 */
#include <stdbool.h>
#include "imu_interface.h"
// Function Pointer variables:
static get_imu_accel_t pfn_stored_get_imu_accel = NULL;
static get_imu_gyros_t pfn_stored_get_imu_gyros = NULL;
static get_imu_mag_t pfn_stored_get_imu_mag = NULL;

bool set_imu_accelFunction(get_imu_accel_t pfn_fptr)
{
	bool ret_val = true;

    if (pfn_fptr == NULL)
    {
        ret_val = false;
    }
    else
    {
        pfn_stored_get_imu_accel = pfn_fptr;
        // Redundant Check for hardware/memory failure
        if (pfn_stored_get_imu_accel != pfn_fptr)
        {
            ret_val = false;
        }
    }
	return ret_val;
}

bool set_imu_gyrosFunction(get_imu_gyros_t pfn_fptr)
{
	bool ret_val = true;

    if (pfn_fptr == NULL)
    {
        ret_val = false;
    }
    else
    {
	    pfn_stored_get_imu_gyros = pfn_fptr;
        // Redundant Check for hardware/memory failure
	    if (pfn_stored_get_imu_gyros != pfn_fptr)
        {
            ret_val = false;
        }
    }
	return ret_val;
}

bool set_imu_magFunction(get_imu_mag_t pfn_fptr)
{
	bool ret_val = true;

    if (pfn_fptr == NULL)
    {
        ret_val = false;
    }
    else
    {
	    pfn_stored_get_imu_mag = pfn_fptr;
        // Redundant Check for hardware/memory failure
	    if (pfn_stored_get_imu_mag != pfn_fptr)
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

bool get_imu_data(imu_axis_data_t* st_imu_accel_data,
				  imu_axis_data_t* st_imu_gyros_data,
				  imu_axis_data_t* st_imu_magnet_data)                    
{
	bool ret_val = true;
	if (pfn_stored_get_imu_accel != NULL)
    {
		ret_val = ret_val && pfn_stored_get_imu_accel(&(st_imu_accel_data->f32_x),
                                                      &(st_imu_accel_data->f32_y),
                                                      &(st_imu_accel_data->f32_z));
	}
    else
    {
		ret_val = false;
	}
	if (pfn_stored_get_imu_gyros != NULL)
    {
		ret_val = ret_val && pfn_stored_get_imu_gyros(&(st_imu_gyros_data->f32_x),
                                                      &(st_imu_gyros_data->f32_y),
                                                      &(st_imu_gyros_data->f32_z));
	}
    else
    {
		ret_val = false;
	}
	if (pfn_stored_get_imu_mag != NULL)
    {
		ret_val = ret_val && pfn_stored_get_imu_mag(&(st_imu_magnet_data->f32_x),
                                                    &(st_imu_magnet_data->f32_y),
                                                    &(st_imu_magnet_data->f32_z));
	}
    else
    {
		ret_val = false;
	}

	return ret_val;
}