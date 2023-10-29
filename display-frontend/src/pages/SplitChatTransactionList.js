import NavigationButtons from "../components/navigationButtons/navigationButtons";
import SplitChatTransactionList from "../components/splitChatTransactionList/splitChatTransactionList"

function SplitChatPage() {
    return (
        <div class="p-3 mb-2 bg-dark text-white" style={{ height: '100vh' }}>
            <SplitChatTransactionList />
            <NavigationButtons class="position-absolute top-100 start-50 translate-middle" />
        </div>
    )
}

export default SplitChatPage