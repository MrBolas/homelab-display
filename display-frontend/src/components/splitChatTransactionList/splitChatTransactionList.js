import React, { useState,useEffect } from "react";
import SplitChatClient from "../../client/split-chat";
import { DataGrid } from '@mui/x-data-grid';

const columns = [
    { field: 'name', headerName: 'Name', width: 350 },
    { field: 'group', headerName: 'Group', width: 130 },
    { field: 'amount', headerName: 'Amount', width: 130 },
    { field: 'description', headerName: 'Description', width: 600 },
    { field: 'createdAt',headerName: 'Created At', width: 130 },
  ];

  const formatTransactions = (transactions) => {
    let formattedTransactions = [];

    for (const key in transactions) {
        formattedTransactions.push({
            id: key,
            name: transactions[key].user.FirstName + " " + transactions[key].user.LastName,
            group: transactions[key].group.GroupName,
            amount: transactions[key].amount,
            description: transactions[key].description,
            createdAt: transactions[key].created_at
        })
    }

    return formattedTransactions;
  }

function SplitChatTransactionList() {
    const [transactions, setTransactions] = useState([]);
    const fetchTransactions = async () => {
    const client = new SplitChatClient("http://100.75.66.10:30500");
    return client.getTransactionList()
        .then(res => {
            const formattedTransactions = formatTransactions(res.transactions);
            setTransactions(formattedTransactions);
        }).catch(error => {
            console.log(error);
        });
    }

    useEffect(() => {
        fetchTransactions();
        const interval = setInterval(() => {
            fetchTransactions();
        }, 150000);
        return () => {
          clearInterval(interval);
        };
      }, []);

      return (
        <div style={{ height: '95%', width: '100%', backgroundColor: 'white', borderRadius: '5px' }}>
          <DataGrid
            rows={transactions}
            columns={columns}

          />
        </div>
      );
}

export default SplitChatTransactionList