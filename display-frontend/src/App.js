import './App.css';

import NavigationButtons from "./components/navigationButtons/navigationButtons";
import WidgetCarousell from "./components/carousel/carousel"
import ClockPage from './pages/Clock';
import { Route, Routes } from 'react-router-dom';
import VerticalGardenPage from './pages/VerticalGarden';
import SplitChatPage from './pages/SplitChatTransactionList';

import '@coreui/coreui/dist/css/coreui.min.css'

function App() {

  /*
      <div class="card w-50 position-absolute top-50 start-50 translate-middle">
        <div class="card-body">
          <h5 class="card-title">Card title</h5>
          <p class="card-text">With supporting text below as a natural lead-in to additional content.</p>
          <a href="#" class="btn btn-primary">Button</a>
                    <NavigationButtons class="position-absolute top-100 start-50 translate-middle" />
        </div>
      </div>
  */
  return (
    <div className="App">
      <Routes>
        <Route path='/' element={<ClockPage />} />
        <Route path='/garden' element={<VerticalGardenPage/>} />
        <Route path='/carousel' element={<WidgetCarousell />} />
        <Route path='/split-chat' element={< SplitChatPage/>} />
      </Routes>

      <script src="https://cdn.jsdelivr.net/npm/@coreui/coreui@4.2.0/dist/js/coreui.bundle.min.js" integrity="sha384-n0qOYeB4ohUPebL1M9qb/hfYkTp4lvnZM6U6phkRofqsMzK29IdkBJPegsyfj/r4" crossorigin="anonymous"></script>
    </div>
  );
}

export default App;
