import argparse
import math
import multiprocessing
from functools import partial

def is_power_of_two(n):
    if n <= 0:
        return False
    return (n & (n - 1)) == 0

def is_prime(n):
    if n <= 1:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True

def is_fibonacci(n):
    if n < 0:
        return False
    a, b = 0, 1
    while a <= n:
        if a == n:
            return True
        a, b = b, a + b
    return False

def get_neighbor_sum(matrix, i, j):
    rows = len(matrix)
    cols = len(matrix[0]) if rows > 0 else 0
    total = 0
    
    for di in [-1, 0, 1]:
        for dj in [-1, 0, 1]:
            if di == 0 and dj == 0:
                continue
            ni = (i + di) % rows
            nj = (j + dj) % cols
            cell = matrix[ni][nj]
            
            if cell == 'O':
                total += 3
            elif cell == 'o':
                total += 1
            elif cell == 'x':
                total -= 1
            elif cell == 'X':
                total -= 3
            # '.' adds 0
    
    return total

def process_cell(matrix, i, j):
    cell = matrix[i][j]
    neigh_count_sum = get_neighbor_sum(matrix, i, j)
    
    # Rule 2: Healthy 'O' cell
    if cell == 'O':
        if is_fibonacci(neigh_count_sum):
            return '.'
        elif neigh_count_sum < 12:
            return 'o'
        else:
            return 'O'
    
    # Rule 3: Weakened 'o' cell
    elif cell == 'o':
        if neigh_count_sum < 0:
            return '.'
        elif neigh_count_sum > 6:
            return 'O'
        else:
            return 'o'
    
    # Rule 4: Dead cell
    elif cell == '.':
        if is_power_of_two(neigh_count_sum):
            return 'o'
        elif is_power_of_two(abs(neigh_count_sum)):
            return 'x'
        else:
            return '.'
    
    # Rule 5: Weakened 'x' cell
    elif cell == 'x':
        if neigh_count_sum >= 1:
            return '.'
        elif neigh_count_sum < -6:
            return 'X'
        else:
            return 'x'
    
    # Rule 6: Healthy 'X' cell
    elif cell == 'X':
        if is_prime(abs(neigh_count_sum)):
            return '.'
        elif neigh_count_sum > -12:
            return 'x'
        else:
            return 'X'
    
    # Default case (shouldn't happen with valid input)
    return cell

def process_matrix_serial(matrix):
    rows = len(matrix)
    cols = len(matrix[0]) if rows > 0 else 0
    new_matrix = [[None for _ in range(cols)] for _ in range(rows)]
    
    for i in range(rows):
        for j in range(cols):
            new_matrix[i][j] = process_cell(matrix, i, j)
    
    return new_matrix

def process_row(args):
    i, matrix = args
    cols = len(matrix[0]) if len(matrix) > 0 else 0
    new_row = []
    
    for j in range(cols):
        new_row.append(process_cell(matrix, i, j))
    
    return (i, new_row)

def process_matrix_parallel(matrix, num_processes):
    rows = len(matrix)
    cols = len(matrix[0]) if rows > 0 else 0
    new_matrix = [[None for _ in range(cols)] for _ in range(rows)]
    
    with multiprocessing.Pool(processes=num_processes) as pool:
        results = pool.map(process_row, [(i, matrix) for i in range(rows)])
    
    for i, row in results:
        new_matrix[i] = row
    
    return new_matrix

def read_matrix(file_path):
    with open(file_path, 'r') as f:
        matrix = [list(line.strip()) for line in f if line.strip()]
    
    # Validate matrix
    if not matrix:
        raise ValueError("Empty matrix")
    
    cols = len(matrix[0])
    for row in matrix:
        if len(row) != cols:
            raise ValueError("All rows must have the same number of columns")
        
        for cell in row:
            if cell not in ['O', 'o', 'X', 'x', '.']:
                raise ValueError(f"Invalid cell character: {cell}")
    
    return matrix

def write_matrix(matrix, file_path):
    with open(file_path, 'w') as f:
        for row in matrix:
            f.write(''.join(row) + '\n')

def main():
    print("Project :: R11846096")  
    
    parser = argparse.ArgumentParser(description='Cellular Life Simulator')
    parser.add_argument('-i', required=True, help='Path to input file')
    parser.add_argument('-o', required=True, help='Path to output file')
    parser.add_argument('-p', type=int, default=1, help='Number of processes')
    
    args = parser.parse_args()
    
    # Validate arguments
    if args.p <= 0:
        raise ValueError("Number of processes must be positive")
    
    # Read input matrix
    matrix = read_matrix(args.i)
    
    # Process 100 iterations
    for _ in range(100):
        if args.p == 1:
            matrix = process_matrix_serial(matrix)
        else:
            matrix = process_matrix_parallel(matrix, args.p)
    
    # Write output matrix
    write_matrix(matrix, args.o)

if __name__ == '__main__':
    main()
