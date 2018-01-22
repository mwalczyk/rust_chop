extern crate libc;

use libc::{uint32_t, size_t, c_float};
use std::slice;

// Parameters:
// chan_data: the float* of channel data from C++
// chan_index: the numeric index of the channel
// chan_samples: the number of samples in this channel
// execute_count: the number of times this CHOP has executed

#[no_mangle]
pub extern fn execute_rs(chan_data: *mut c_float,		
					     chan_index: size_t, 			
					     chan_samples: size_t, 			
					     execute_count: uint32_t) {		

	// Create a slice from the raw channel data
	let mut data = unsafe {
		assert!(!chan_data.is_null());
		slice::from_raw_parts_mut(chan_data, chan_samples as usize)
	};

	// Construct a sin wave
	let phase = 2.0 * std::f64::consts::PI;
	let sample_rate = 60.0;

	for (index, elem) in data.iter_mut().enumerate() {
		let percent = (index as f64) / (chan_samples as f64);
		let timestep = (execute_count as f64) / sample_rate;
		let val = (phase * percent + timestep).sin();

    	*elem = val as f32;
	}
}





