import React, { useState,useEffect } from "react";
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import SplitChatClient from "../../client/split-chat";

function SplitChatTransactionList() {
    const [transactions, setTransactions] = useState([]);
    const fetchTransactions = async () => {
    const client = new SplitChatClient("http://localhost:8080");
    return client.getTransactionList()
        .then(res => {
            setTransactions(res.transactions);
            console.log(res.transactions);
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
        <TableContainer component={Paper}>
          <Table sx={{ minWidth: 650 }} aria-label="simple table">
            <TableHead>
              <TableRow>
                <TableCell align="left">User</TableCell>
                <TableCell align="right">Group</TableCell>
                <TableCell align="right">Ammount</TableCell>
                <TableCell align="right">Description</TableCell>
                <TableCell align="right">CreatedAt</TableCell>
              </TableRow>
            </TableHead>
            <TableBody>
        {transactions.map((transaction) => (
          <TableRow
            key={transaction.name}
            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
          >
            <TableCell component="th" scope="row">
            {transaction?.user.FirstName} {transaction?.user.LastName}
            </TableCell>
            <TableCell align="right">{transaction?.group.GroupName}</TableCell>
            <TableCell align="right">{transaction?.amount}</TableCell>
            <TableCell align="right">{transaction?.description}</TableCell>
            <TableCell align="right">{transaction?.created_at}</TableCell>
          </TableRow>
        ))}
      </TableBody>
          </Table>
        </TableContainer>
      );
}

export default SplitChatTransactionList