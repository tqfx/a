/*!
An algorithm library based on C/C++ language

## Installation

Add this to your `Cargo.toml`:

```toml
[dependencies]
liba = "0.1"
```
*/

#![warn(missing_docs)]
#![allow(non_camel_case_types)]
#![cfg_attr(not(features = "std"), no_std)]

use core::ffi::c_char;
/// Equivalent to C’s int type.
pub type int = core::ffi::c_int;
/// Equivalent to C’s unsigned int type.
pub type uint = core::ffi::c_uint;
/// floating-point number stored using `f64`
#[cfg(not(feature = "float"))]
pub type float = f64;
/// floating-point number stored using `f32`
#[cfg(feature = "float")]
pub type float = f32;
/// floating-point number union
#[repr(C)]
pub union Float {
    /// as a floating-point number
    pub f: float,
    /// as a floating-point array
    pub p: *mut float,
}

pub mod crc;
pub mod mf;
pub mod pid;
pub mod polytrack;
pub mod tf;
pub mod version;

extern "C" {
    fn a_version() -> *const c_char;
}

/**
algorithm library version

## Examples

```
println!("version {}", liba::version());
```
*/
pub fn version() -> &'static str {
    unsafe {
        core::ffi::CStr::from_ptr(a_version())
            .to_str()
            .unwrap_unchecked()
    }
}

extern "C" {
    fn a_f32_rsqrt(x: f32) -> f32;
    fn a_f64_rsqrt(x: f64) -> f64;
}

/// fast inverse square-root, $ \frac{1}{\sqrt{x}} $
pub fn f32_rsqrt(x: f32) -> f32 {
    unsafe { a_f32_rsqrt(x) }
}

/// fast inverse square-root, $ \frac{1}{\sqrt{x}} $
pub fn f64_rsqrt(x: f64) -> f64 {
    unsafe { a_f64_rsqrt(x) }
}

#[cfg(test)]
mod test {
    extern crate std;
    #[test]
    fn version() {
        std::println!("version {}", crate::version());
    }
    #[test]
    fn rsqrt() {
        std::println!("1/sqrt({})={}", 4, crate::f32_rsqrt(4.0));
        std::println!("1/sqrt({})={}", 4, crate::f64_rsqrt(4.0));
    }
}
