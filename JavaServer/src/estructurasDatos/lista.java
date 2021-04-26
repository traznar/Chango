package estructurasDatos;



import java.util.Arrays;


public class lista<T> {

	
	private static final int INITIAL_CAPACITY = 10;


	private Object elementData[] = {};

	private int size = 0;

	public lista() {
		elementData = new Object[INITIAL_CAPACITY];
	}


	public void add(T element) {

		if (size == elementData.length) {
			ensureCapacity();
		}

		elementData[size++] = element;
	}


	@SuppressWarnings("unchecked")
	public T get(int index) {

		if (index < 0 || index >= size) {
			throw new IndexOutOfBoundsException("Invalid index passed !!");
		}

		return (T)elementData[index];
	}

	public Object remove(int index) {
		/* Check for invalid index */
		if (index < 0 || index >= size) {
			throw new IndexOutOfBoundsException("Invalid index passed !!");
		}

		Object removedElement = elementData[index];

		for (int i = index; i < size; i++) {
			elementData[i] = elementData[i + 1];
		}
		size--;
		return removedElement;
	}

	public Object[] toArray() {
		return Arrays.copyOf(elementData, size);
	}

	public boolean contains(T element) {
		/* Element should not be null */
		if (element == null) {
			throw new IllegalArgumentException("Invalid input. Cannot be null !!");
		}
		/* Compare the element with each entry */
		for (Object object : elementData) {
			if (object != null && object.equals(element)) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Method to check the size of list
	 * 
	 * @return {@link int}
	 */
	public int size() {
		return size;
	}

	/**
	 * Method to check if list is empty
	 * 
	 * @return {@link boolean}
	 */
	public boolean isEmpty() {
		return size == 0;
	}

	/**
	 * Method to clear the list
	 */
	public void clearAll() {
		/* Create the element data again and set size to 0 */
		elementData = new Object[INITIAL_CAPACITY];
		size = 0;
	}

	public void display() {
		for (int i = 0; i < size; i++) {
			System.out.println("Index = " + i + ", Element = " + elementData[i]);
		}
	}

	private void ensureCapacity() {
		int newIncreasedCapacity = elementData.length * 2;
		elementData = Arrays.copyOf(elementData, newIncreasedCapacity);
	}

}