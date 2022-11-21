from mpi4py import MPI
import random

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

rank_for_visit = list(range(1, size))
processor_name = f"proc_{rank}"

if rank == 0:
    comm.ssend((rank, [rank]), dest=random.choice(rank_for_visit))
else:
    rank_from, ranks_visited = comm.recv()
    print(f"Hello to {processor_name} from proc_{rank_from}", flush=True)
    ranks_visited.append(rank)
    not_visited = [x for x in rank_for_visit if x not in ranks_visited]
    if not_visited:
        comm.ssend((rank, ranks_visited), dest=random.choice(not_visited))

MPI.Finalize()
