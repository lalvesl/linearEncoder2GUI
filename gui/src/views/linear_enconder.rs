use leptos::{leptos_dom::helpers::IntervalHandle, *};
use serde::{Deserialize, Serialize};
use serde_wasm_bindgen::to_value;
use std::time::Duration;
use wasm_bindgen::prelude::*;

use std::ops::{Add, Sub};

#[wasm_bindgen]
extern "C" {
    #[wasm_bindgen(js_namespace = ["window", "__TAURI__", "tauri"])]
    async fn invoke(cmd: &str, args: JsValue) -> JsValue;
}

#[derive(Serialize, Deserialize)]
struct PositionArgs<'a> {
    data: &'a str,
}

use crate::components::header::Header;

#[component]
pub fn LinearEnconder() -> impl IntoView {
    let (position, set_position) = create_signal(0.123);

    use_interval(20, move || {
        spawn_local(async move {
            let args = to_value(&PositionArgs { data: &"" }).unwrap();
            let new_position = invoke("get_new_position", args).await.as_f64().unwrap();
            set_position.set(new_position);
        })
    });

    //()

    view! {
        <div id="imgbgd"></div>
        <div id="imgbgdblur"></div>
        <Header/>
        <main class="init-main">
            <h1>{move || format!("{:.3}", position.get())} {" "}mm</h1>
        </main>
    }
}

pub fn use_interval<T, F>(interval_millis: T, f: F)
where
    F: Fn() + Clone + 'static,
    T: Into<MaybeSignal<u64>> + 'static,
{
    let interval_millis = interval_millis.into();
    create_effect(move |prev_handle: Option<IntervalHandle>| {
        // effects get their previous return value as an argument
        // each time the effect runs, it will return the interval handle
        // so if we have a previous one, we cancel it
        if let Some(prev_handle) = prev_handle {
            prev_handle.clear();
        };

        // here, we return the handle
        set_interval_with_handle(
            f.clone(),
            // this is the only reactive access, so this effect will only
            // re-run when the interval changes
            Duration::from_millis(interval_millis.get()),
        )
        .expect("could not create interval")
    });
}
