
class GardenClient {
    _path

    constructor(path) {
        this._path = path;
    }

    async hasWater() {
        return fetch(this._path + "/haswater")
            .then(response => response.status === 200
                ? response.json()
                : Promise.reject(response))
            .then(data => data.hasWater)
            .catch(error => console.log(error));
    }
}

export default GardenClient;