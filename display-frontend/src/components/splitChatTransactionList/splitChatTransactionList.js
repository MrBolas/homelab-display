import React, { useState,useEffect } from "react";
import SplitChatClient from "../../client/split-chat";
import red from '@mui/material/colors/red';
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
    const client = new SplitChatClient("http://localhost:8080");
    return client.getTransactionList()
        .then(res => {
            const formattedTransactions = formatTransactions(res.transactions);
            setTransactions(formattedTransactions);
            console.log(formattedTransactions);
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
        <div style={{ height: '100%', width: '100%', accentColor: red }}>
          <DataGrid
            rows={transactions}
            columns={columns}

          />
        </div>
      );
}

export default SplitChatTransactionList