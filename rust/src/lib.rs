extern crate libc;

use libc::{uint32_t, size_t, c_float};
use std::slice;

// This function should not be modified! 
#[no_mangle]
pub extern fn execute_rs(chan_data: *mut c_float,		
					     chan_index: size_t, 			
					     chan_samples: size_t, 			
					     execute_count: uint32_t) {		

	// Create a slice from the raw channel data - note that this does 
	// not perform a copy! The resulting slice will share the same 
	// underlying memory as the raw, C-style array coming from
	// TouchDesigner.
	let mut data = unsafe {
		// We need to make sure that the pointer is not NULL before 
		// constructing the slice.
		assert!(!chan_data.is_null());
		slice::from_raw_parts_mut(chan_data, chan_samples as usize)
	};

	execute(&mut data, chan_index as usize, chan_samples as usize, execute_count as u32);
}


// This is the client-facing, safe version of the function above.
// Authors should write their code inside of this function rather
// than the unsafe block above.
//
// Parameters:
// chan_data: a slice containing the mutable channel data
// chan_index: the numeric index of the channel
// chan_samples: the number of samples in this channel
// execute_count: the number of times this CHOP has executed
// 
// This function will be called once for each output channel
// of the CPlusPlus CHOP.
pub fn execute(chan_data: &mut [f32],
			   chan_index: usize,
			   chan_samples: usize,
			   execute_count: u32) {

	// As a simple example, output a sin wave.
	let phase = (2.0 * std::f64::consts::PI) / (chan_index as f64 + 1.0);
	let sample_rate = 60.0;

	for (index, elem) in chan_data.iter_mut().enumerate() {
		let percent = (index as f64) / (chan_samples as f64);
		let timestep = (execute_count as f64) / sample_rate;
		let val = (phase * percent + timestep).sin();

    	*elem = val as f32;
	}
}


