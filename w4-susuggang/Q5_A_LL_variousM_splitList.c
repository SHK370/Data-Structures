// // Method 1: Counting Nodes and Splitting

//     // Step 1: Count the total number of nodes
//     int count = 0;
//     ListNode *current = ll->head;
    
// 	while (current != NULL) {
//         count++;
//         current = current->next;
//     }

//     // Step 2: Calculate the midpoint
//     int mid = (count + 1) / 2; // Ensure frontList has one more node if count is odd

//     // Step 3: Traverse to the node before midpoint
//     current = ll->head;
//     ListNode *prev = NULL;
//     for (int i = 0; i < mid; i++) {
//         prev = current;
//         current = current->next;
//     }

//     // Split the list
//     if (prev != NULL) {
//         prev->next = NULL; // Terminate the front list
//     }

//     // Initialize frontList
//     frontList->head = ll->head;
//     frontList->size = mid;

//     // Initialize backList
//     backList->head = current;
//     backList->size = count - mid;


// // -------------


