mod app;
mod components;
mod views;

use app::App;

use leptos::*;

fn main() {
    mount_to_body(|| {
        view! {
            <App/>
        }
    })
}
