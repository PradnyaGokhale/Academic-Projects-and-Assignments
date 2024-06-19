#!/usr/bin/env python
# coding: utf-8

# In[2]:


from queue import PriorityQueue

class State:
    def __init__(self, lM, lC, rM, rC, boat, parent=None):
        self.lM = lM
        self.lC = lC
        self.rM = rM
        self.rC = rC
        self.boat = boat
        self.parent = parent
        self.cost = 0

    def is_goal(self):
        return self.lM == 0 and self.lC == 0

    def is_valid(self):
        if self.lM < 0 or self.lC < 0 or self.rM < 0 or self.rC < 0:
            return False
        if self.lM > 3 or self.lC > 3 or self.rM > 3 or self.rC > 3:
            return False
        if (self.lC > self.lM > 0) or (self.rC > self.rM > 0):
            return False
        return True

    def successors(self):
        successors = []
        if self.boat == 'left':
            # Boat travels from left to right
            for i in range(3):
                for j in range(3):
                    if 1 <= i + j <= 2:
                        new_state = State(self.lM - i, self.lC - j, self.rM + i, self.rC + j, 'right', self)
                        if new_state.is_valid():
                            new_state.cost = self.cost + 1
                            successors.append(new_state)
        else:
            # Boat travels from right to left
            for i in range(3):
                for j in range(3):
                    if 1 <= i + j <= 2:
                        new_state = State(self.lM + i, self.lC + j, self.rM - i, self.rC - j, 'left', self)
                        if new_state.is_valid():
                            new_state.cost = self.cost + 1
                            successors.append(new_state)
        return successors

    def __eq__(self, other):
        return self.lM == other.lM and self.lC == other.lC and self.rM == other.rM and self.rC == other.rC and self.boat == other.boat

    def __lt__(self, other):
        return self.cost < other.cost
    
    def __hash__(self):
        return hash((self.lM, self.lC, self.rM, self.rC, self.boat))


def astar():
    initial_state = State(3, 3, 0, 0, 'left')
    if initial_state.is_goal():
        return initial_state
    frontier = PriorityQueue()
    frontier.put(initial_state)
    explored = set()
    while not frontier.empty():
        state = frontier.get()
        explored.add(state)
        for successor in state.successors():
            if successor.is_goal():
                return successor
            if successor not in explored:
                frontier.put(successor)
    return None

def print_solution(solution):
    path = []
    while solution:
        path.append(solution)
        solution = solution.parent
    path.reverse()
    for i, state in enumerate(path):
        print(f"Step {i}:")
        print_state(state)
        print()

def print_state(state):
    print("Left side:", state.lM, "missionaries,", state.lC, "cannibals")
    print("Right side:", state.rM, "missionaries,", state.rC, "cannibals")
    print("Boat is on", state.boat, "side")

def main():
    solution = astar()
    if solution:
        print("Solution found!")
        print_solution(solution)
    else:
        print("No solution exists.")

if __name__ == "__main__":
    main()


# In[ ]:




