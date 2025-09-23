<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") { //if the form in the html file calls post, num is imported into this file as $n
    $n = intval($_POST["num"]);

    echo "<h3>Multiplication Table up to $n</h3>"; //print and create style of the php table
    echo "<style> 
            table, td {
                border: 2px solid black;
                border-collapse: collapse;
                text-align: center;
                padding: 5px;
            }
          </style>";
    echo "<table>"; //start table

    // First row (header row: 0, 1, 2, ..., n)
    echo "<tr><td>0</td>"; //create first row (0 to $n)
    for ($col = 1; $col <= $n; $col++) {
        echo "<td>$col</td>";
    }
    echo "</tr>"; //end first row

    // Remaining rows
    for ($row = 1; $row <= $n; $row++) {
        echo "<tr>"; //start row
        echo "<td>$row</td>"; // Row index
        for ($col = 1; $col <= $n; $col++) {
            echo "<td>" . ($row * $col) . "</td>"; //concatenate <td> + row * col + </td>
        }
        echo "</tr>"; //end row and loop again to next row
    }

    echo "</table>";//end table
}
?>
