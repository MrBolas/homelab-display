
class GardenClient {
    _path

    constructor(path) {
        this._path = path;
    }

    async hasWater() {
        return fetch(this._path + "/api/v1/latest-waterlevel")
            .then(response => response.status === 200
                ? response.json()
                : Promise.reject(response))
            .then(data => data)
            .catch(error => console.log(error));
    }
}

export default GardenClient;