use leptos::*;

use crate::components::header::Header;

#[component]
pub fn InitView() -> impl IntoView {
    let position: f64 = 0.0;
    view! {
        <div id="imgbgd"></div>
        <div id="imgbgdblur"></div>
        <Header/>
        <main class="init-main">
            <h1>{{position}} {{" "}}mm</h1>
        </main>
    }
}
