/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_3
 *
 * ListTest.java - Taken and slightly modified from...
 * https://github.com/legendddhgf/cmps101-pt.s18.grading/blob/master/pa3/ModelListTest.java
 */

public class ListTest {
	public static void main(String[] args) {

		List A;
		List B;

		// Empty_Length Test
		A = new List();
		if (A.length() != 0) {
			System.out.println("Failed Empty_Length");
		}
		// Append_Length Test
		A = new List();
		A.append(1);
		A.append(2);
		A.append(3);
		A.append(5);
		if (A.length() != 4) {
			System.out.println("Failed Append_Length");
		}
		// Prepend_Length Test
		A = new List();
		A.prepend(6);
		A.prepend(4);
		A.prepend(2);
		A.prepend(1);
		if (A.length() != 4) {
			System.out.println("Failed Prepend_Length");
		}
		// InsertAfter_Length Test
		A = new List();
		A.append(1);
		A.append(2);
		A.append(3);
		A.append(5);
		A.moveFront();
		A.insertAfter(12);
		if (A.length() != 5) {
			System.out.println("Failed InsertAfter_Length");
		}
		// InsertBefore_Length Test
		A = new List();
		A.prepend(76);
		A.prepend(4);
		A.prepend(3);
		A.prepend(1);
		A.moveFront();
		A.insertBefore(115);
		if (A.length() != 5) {
			System.out.println("Failed InsertBefore_Length");
		}
		// DeleteFront_Length Test
		A = new List();
		A.prepend(76);
		A.prepend(4);
		A.deleteFront();
		A.prepend(3);
		A.prepend(1);
		A.moveFront();
		A.insertBefore(115);
		A.deleteFront();
		if (A.length() != 3) {
			System.out.println("Failed DeleteFront_Length");
		}
		// DeleteBack_Length Test
		A = new List();
		A.append(1);
		A.deleteBack();
		A.append(2);
		A.append(3);
		A.append(5);
		A.moveFront();
		A.insertAfter(12);
		A.deleteBack();
		if (A.length() != 3) {
			System.out.println("Failed DeleteBack_Length");
		}
		// Delete_Length Test
		A = new List();
		A.append(1);
		A.append(2);
		A.moveFront();
		A.delete();
		A.append(3);
		A.append(5);
		A.moveFront();
		A.insertAfter(12);
		A.delete();
		if (A.length() != 3) {
			System.out.println("Failed Delete_Length");
		}
		// EmptyList_Index Test
		A = new List();
		if (A.index() != -1) {
			System.out.println("Failed EmptyList_Index");
		}
		// MoveFront_Index Test
		A = new List();
		A.append(1);
		A.append(5);
		A.append(16);
		A.append(176);
		A.append(3214);
		A.moveFront();
		if (A.index() != 0) {
			System.out.println("Failed MoveFront_Index");
		}
		// MoveBack_Index Test
		A = new List();
		A.append(1);
		A.append(5);
		A.append(16);
		A.append(176);
		A.append(3214);
		A.moveBack();
		if (A.index() != 4) {
			System.out.println("Failed MoveBack_Index");
		}
		// MoveNext_Index Test
		A = new List();
		A.append(1);
		A.append(5);
		A.append(16);
		A.append(176);
		A.append(3214);
		A.moveFront();
		A.moveNext();
		A.moveNext();
		if (A.index() != 2) {
			System.out.println("Failed MoveNext_Index 1");
		}
		A.moveNext();
		A.moveNext();
		A.moveNext();
		if (A.index() != -1) {
			System.out.println("Failed MoveNext_Index 2");
		}
		// MovePrev_Index Test
		A = new List();
		A.append(1);
		A.append(5);
		A.append(3214);
		A.moveBack();
		A.movePrev();
		if (A.index() != 1) {
			System.out.println("Failed MovePrev_Index 1");
		}
		A.movePrev();
		A.movePrev();
		if (A.index() != -1) {
			System.out.println("Failed MovePrev_Index 2");
		}
		// Append_Index Test
		A = new List();
		A.append(1);
		A.append(5);
		A.append(7);
		A.moveBack();
		A.append(45);
		A.append(51);
		A.append(3214);
		if (A.index() != 2) {
			System.out.println("Failed Append_Index 1");
		}
		A.moveBack();
		A.movePrev();
		A.movePrev();
		if (A.index() != 3) {
			System.out.println("Failed Append_Index 2");
		}
		A.moveFront();
		A.movePrev();
		if (A.index() != -1) {
			System.out.println("Failed Append_Index 3");
		}
		// Prepend_Index Test
		A = new List();
		A.prepend(1);
		A.prepend(5);
		A.prepend(7);
		A.moveFront();
		A.prepend(45);
		A.prepend(51);
		A.prepend(3214);
		A.prepend(314);
		A.prepend(324);
		if (A.index() != 5) {
			System.out.println("Failed Prepend_Index 1");
		}
		A.moveBack();
		A.movePrev();
		A.prepend(234);
		A.movePrev();
		if (A.index() != 6) {
			System.out.println("Failed Prepend_Index 2");
		}
		A.moveFront();
		A.movePrev();
		if (A.index() != -1) {
			System.out.println("Failed Prepend_Index 3");
		}
		// InsertAfter_Index Test
		A = new List();
		A.append(5);
		A.append(6);
		A.append(4);
		A.append(33);
		A.append(2);
		A.append(1);
		A.moveBack();
		A.insertAfter(75);
		A.moveNext();
		if (A.index() != 6) {
			System.out.println("Failed InsertAfter_Index 1");
		}
		A.insertAfter(345);
		A.moveBack();
		if (A.index() != 7) {
			System.out.println("Failed InsertAfter_Index 2");
		}
		// InsertBefore_Index Test
		A = new List();
		A.prepend(34);
		A.prepend(4);
		A.prepend(354);
		A.prepend(3674);
		A.moveBack();
		A.insertBefore(435);
		if (A.index() != 4) {
			System.out.println("Failed InsertBefore_Index 1");
		}
		A.prepend(324);
		A.prepend(33464);
		A.prepend(3498);
		A.moveFront();
		A.insertBefore(67);
		if (A.index() != 1) {
			System.out.println("Failed InsertBefore_Index 2");
		}
		// DeleteFront_Index Test
		A = new List();
		A.prepend(5);
		A.prepend(65);
		A.prepend(43);
		A.prepend(2);
		A.prepend(8);
		A.prepend(1);
		A.moveFront();
		A.deleteFront();
		if (A.index() != -1) {
			System.out.println("Failed DeleteFront_Index 1");
		}
		A.moveBack();
		A.deleteFront();
		if (A.index() != 3) {
			System.out.println("Failed DeleteFront_Index 2");
		}
		// DeleteBack_Index Test
		A = new List();
		A.prepend(5);
		A.prepend(65);
		A.prepend(43);
		A.prepend(2);
		A.prepend(8);
		A.prepend(1);
		A.moveBack();
		A.deleteBack();
		if (A.index() != -1) {
			System.out.println("Failed DeleteBack_Index 1");
		}
		A.moveFront();
		A.deleteBack();
		A.moveNext();
		if (A.index() != 1) {
			System.out.println("Failed DeleteBack_Index 2");
		}
		// Delete_Index Test
		A = new List();
		A.prepend(5);
		A.prepend(65);
		A.prepend(43);
		A.moveBack();
		A.delete();
		if (A.index() != -1) {
			System.out.println("Failed Delete_Index 1");
		}
		A.prepend(2);
		A.prepend(8);
		A.prepend(1);
		A.moveBack();
		if (A.index() != 4) {
			System.out.println("Failed Delete_Index 2");
		}
		A.delete();
		A.moveBack();
		if (A.index() != 3) {
			System.out.println("Failed Delete_Index 3");
		}
		A.moveFront();
		A.delete();
		A.moveFront();
		if (A.index() != 0) {
			System.out.println("Failed Delete_Index 4");
		}
		A.delete();
		if (A.index() != -1) {
			System.out.println("Failed Delete_Index 5");
		}
		// Append_Equals Test
		A = new List();
		B = new List();
		A.append(1);
		B.append(1);
		A.append(2);
		if (A.equals(B)) {
			System.out.println("Failed Append_Equals 1");
		}
		B.append(2);
		if (!A.equals(B)) {
			System.out.println("Failed Append_Equals 2");
		}
		// Prepend_Equals Test
		A = new List();
		B = new List();
		A.prepend(1);
		B.prepend(1);
		A.prepend(2);
		if (A.equals(B)) {
			System.out.println("Failed Prepend_Equals 1");
		}
		B.prepend(2);
		if (!A.equals(B)) {
			System.out.println("Failed Prepend_Equals 2");
		}
		// InsertAfter_Equals Test
		A = new List();
		B = new List();
		A.append(1);
		B.append(1);
		A.append(2);
		B.moveFront();
		B.insertAfter(2);
		if (!A.equals(B)) {
			System.out.println("Failed InsertAfter_Equals 1");
		}
		B.append(3);
		A.moveBack();
		A.insertAfter(3);
		if (!A.equals(B)) {
			System.out.println("Failed InsertAfter_Equals 2");
		}
		// InsertBefore_Equals Test
		A = new List();
		B = new List();
		A.prepend(1);
		B.prepend(1);
		A.prepend(2);
		B.moveFront();
		B.insertBefore(2);
		if (!A.equals(B)) {
			System.out.println("Failed InsertBefore_Equals 1");
		}
		B.prepend(3);
		A.moveFront();
		A.insertBefore(3);
		if (!A.equals(B)) {
			System.out.println("Failed InsertBefore_Equals 2");
		}
		// DeleteFront_Equals
		A = new List();
		B = new List();
		A.append(1);
		B.append(1);
		A.append(2);
		B.append(2);
		A.deleteFront();
		if (A.equals(B)) {
			System.out.println("Failed DeleteFront_Equals 1");
		}
		B.deleteFront();
		if (!A.equals(B)) {
			System.out.println("Failed DeleteFront_Equals 2");
		}
		A.prepend(3);
		B.prepend(3);
		A.deleteFront();
		B.deleteFront();
		if (!A.equals(B)) {
			System.out.println("Failed DeleteFront_Equals 3");
		}
		// DeleteBack_Equals
		A = new List();
		B = new List();
		A.prepend(1);
		B.prepend(1);
		A.prepend(2);
		B.prepend(2);
		A.deleteBack();
		if (A.equals(B)) {
			System.out.println("Failed DeleteBack_Equals 1");
		}
		B.deleteBack();
		if (!A.equals(B)) {
			System.out.println("Failed DeleteBack_Equals 2");
		}
		A.append(3);
		B.append(3);
		A.deleteBack();
		B.deleteBack();
		if (!A.equals(B)) {
			System.out.println("Failed DeleteBack_Equals 3");
		}
		// Delete_Equals Test
		A = new List();
		B = new List();
		A.prepend(1);
		B.prepend(1);
		A.prepend(2);
		B.prepend(2);
		A.moveBack();
		A.delete();
		if (A.equals(B)) {
			System.out.println("Failed DeleteBack_Equals 1");
		}
		B.moveBack();
		B.delete();
		if (!A.equals(B)) {
			System.out.println("Failed DeleteBack_Equals 2");
		}
		A.append(3);
		B.append(3);
		A.moveBack();
		A.delete();
		B.moveBack();
		B.delete();
		if (!A.equals(B)) {
			System.out.println("Failed DeleteBack_Equals 3");
		}
		// Empty_Clear Test
		A = new List();
		A.clear();
		if (A.index() != -1 || A.length() != 0) {
			System.out.println("Failed Empty_Clear");
		}
		// NonEmpty_Clear Test
		A = new List();
		A.append(1);
		A.prepend(2);
		A.moveFront();
		A.clear();
		if (A.index() != -1 || A.length() != 0) {
			System.out.println("Failed NonEmpty_Clear");
		}
		// Set_Get Test
		A = new List();
		A.append(1);
		A.prepend(2);
		A.deleteFront();
		A.moveBack();
		if (!A.get().equals(1)) {
			System.out.println("Failed Set_Get");
		}
		// Set_Front Test
		A = new List();
		A.append(1);
		A.prepend(5);
		A.moveBack();
		if (!A.front().equals(5)) {
			System.out.println("Failed Set_Front");
		}
		// NonEmpty_Front Test
		A = new List();
		A.prepend(5);
		A.append(7);
		A.prepend(2);
		A.moveFront();
		A.insertBefore(43);
		A.deleteFront();
		A.delete();
		if (!A.front().equals(5)) {
			System.out.println("Failed NonEmpty_Front");
		}
		// Set_Back Test
		A = new List();
		A.prepend(1);
		A.append(5);
		A.moveFront();
		if (!A.back().equals(5)) {
			System.out.println("Failed Set_Back");
		}
		// NonEmpty_Back Test
		A = new List();
		A.append(5);
		A.prepend(7);
		A.append(2);
		A.moveBack();
		A.insertAfter(43);
		A.deleteBack();
		A.delete();
		if (!A.back().equals(5)) {
			System.out.println("Failed NonEmpty_Back");
		}
	}
}
