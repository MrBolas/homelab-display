import NavigationButtons from "../navigationButtons/navigationButtons";

function WidgetCarousel() {
    return (
        <div>
            <div id="carouselExampleSlidesOnly" class="carousel slide" data-coreui-ride="carousel">
                <div class="carousel-inner">
                    <div class="carousel-item active">
                        <img src="https://smartslider3.com/wp-content/uploads/2021/09/carouselexamples-1.png" class="d-block w-100" alt="bananas" />
                    </div>
                    <div class="carousel-item">
                        <img src="..." class="d-block w-100" alt="..." />
                    </div>
                    <div class="carousel-item">
                        <img src="..." class="d-block w-100" alt="..." />
                    </div>
                </div>
            </div>
            <NavigationButtons class="position-absolute top-100 start-50 translate-middle" />
        </div>
    );
}

export default WidgetCarousel;