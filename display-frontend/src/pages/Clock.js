import NavigationButtons from "../components/navigationButtons/navigationButtons";
import Clock from 'react-live-clock';

function ClockPage() {
    return (
        <div class="p-3 mb-2 bg-dark text-white" style={{ height: '100vh' }}>
            <h1 class="align-middle">
                <p class="text-center fs-1">
                    <Clock format={'HH:mm:ss'}
                        ticking={true}
                        style={{ fontSize: '500%' }}
                        timezone={'Europe/Lisbon'} />
                </p>
                Europe/Lisbon
            </h1>
            <NavigationButtons class="position-absolute top-100 start-50 translate-middle" />
        </div>
    )
}

export default ClockPage