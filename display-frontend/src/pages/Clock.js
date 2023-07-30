import NavigationButtons from "../components/navigationButtons/navigationButtons";


function Clock() {
    return (
        <div> 
            This is a clock 
            <NavigationButtons class="position-absolute top-100 start-50 translate-middle" />
        </div>
    )
}

export default Clock