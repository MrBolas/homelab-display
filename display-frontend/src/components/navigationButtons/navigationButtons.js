import { Link, useLocation } from 'react-router-dom';

function buildLinks(linkList, currentPath) {
    let links = []
    for (const link of linkList) {
        console.log("link ", link)
        console.log("current ", currentPath)
        if (link.path === currentPath) {
            links.push(<Link class="btn btn-primary active" to={link.path} >{link.name}</Link>);
        } else {
            links.push(<Link class="btn btn-primary" to={link.path} >{link.name}</Link>);
        }
    }
    return links
}

function NavigationButtons() {
    const location = useLocation();
    const { pathname } = location;

    const links = [
        {id:1, name: "Clock",path: "/",active: false},
        {id:2, name: "Carousel",path: "/carousel",active: false}
    ]

    return (
        <div class="btn-group position-absolute bottom-0 start-50 translate-middle">
            {buildLinks(links, pathname)}
        </div>
    );
}

export default NavigationButtons