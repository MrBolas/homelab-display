class SplitChatClient {
    _path   // path to backend

    constructor(path) {
        this._path = path;
    }

    async getTransactionList() {
        return fetch(this._path + "/v1/transactionList")
            .then(response => response.status === 200
                ? response.json()
                : Promise.reject(response))
            .then(data => data)
            .catch(error => console.log(error));
    }
}

export default SplitChatClient;