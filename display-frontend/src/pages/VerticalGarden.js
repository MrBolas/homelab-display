import NavigationButtons from "../components/navigationButtons/navigationButtons";
import WaterLevel from "../components/waterLevel/waterLevel";

function VerticalGardenPage() {
    return (
        <div class="p-3 mb-2 bg-dark text-white" style={{ height: '100vh' }}>
            <WaterLevel />
            <NavigationButtons class="position-absolute top-100 start-50 translate-middle" />
        </div>
    )
}

export default VerticalGardenPage