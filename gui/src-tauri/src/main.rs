// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use std::fs::{self, File};
use std::io::prelude::*;

#[tauri::command]
fn get_new_position(data: &str) -> f64 {
    let mut position_file = fs::File::options()
        .read(true)
        .write(false)
        .open("../../io/mem/io")
        .expect("Error on open position file");
    let mut position_string = String::new();
    position_file
        .read_to_string(&mut position_string)
        .expect("Error on read position file");
    position_string.truncate(19);
    let position_int = match position_string.parse() {
        Ok(v) => v,
        Err(_) => 0.,
    };
    return (position_int as f64) / 100.;
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![get_new_position])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
