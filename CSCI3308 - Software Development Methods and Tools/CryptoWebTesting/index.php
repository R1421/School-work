<!DOCTYPE html>
<html>
	<head>index.php</head>
	<body>
		<div>
			<p>What the fuck</p>
                        

<?php

include("global.php");
ensure_logged_in();
main();


function main() {
    $username = "Charles";
    findFriendList($username);


    $username = "Kevin";
    findFriendList($username);
}


function findFriendList($username) {

    $db = makePDO()
    $dbUsername = $db->quote($username);
    $dbUers = $db->query("SELECT * FROM WholeNames);

    //Declare threshold percentage and perform sorting algorithm
    $threshold = 80;
    $resolved = array();

    $percentSimilar;
    $lenResolved = 0;
    foreach($dbUsers as $dbUser){
        similar_text( $username, $dbUser, $percentSimilar);
        if($percentSimilar >= $threshold) {
            dbPair = array( $dbUser, $percentSimilar);
            array_push($resolved, dbPair);
            $lenResolved += 1;
        }
    }
    
    $resolved = quickSort( $resolved );

    foreach($resolved as $results) {
        echo $results;
    }

}

function quickSort($list) {
    $listLen = sizeof($list);
    if( $listLen <= 1 ):
        return;
    $pivot = rand(0,$listLen -1);
    $i = 0;
    $j = 0;
    while( $i < $listLen) {
        if( $i < $pivot && $list[$i][1] > $list[$pivot][1] ){
            $j = $i;
            while( $j < $pivot ) {
                $x = $list[$j][1];
                $list[$j][1] = $list[$j + 1][1];
                $list[$j + 1][1] = $x;
                $j += 1;
            }
            $pivot -= 1;
        }
        elif ( $i > $pivot &&  $list[$i][1] < $list[$pivot][1] ) {
            while( $j > $pivot) {
                $x = $list[$j][1];
                $list[$j][1] = $list[$j -1][1];
                $list[$j - 1][1] = $x;
                $j -= 1;
            }
            $pivot += 1;
        }
        else {
            $i += 1;
        }
    }
    $subArray1 = array_slice($list, 0, $pivot);
    $subArray2 = array_slice($list, $pivot, $listLen - 1);
    
    $subArray1 = quickSort($subArray1);
    $subArray2 = quickSort(subArray2);

    return array_merge( $subArray1, $subArray2 );
}
?>







		</div>
	</body>
<html>
