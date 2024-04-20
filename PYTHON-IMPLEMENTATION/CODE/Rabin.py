d = 256
MAX_LENGTH = 1000

def search(pat, txt, q):
    M = len(pat)
    N = len(txt)
    h = pow(d, M-1, q)
    p = 0
    t = 0

    for i in range(M):
        p = (d * p + ord(pat[i])) % q
        t = (d * t + ord(txt[i])) % q

    for i in range(N - M + 1):
        if p == t:
            if txt[i:i+M] == pat:
                print("Pattern found at index", i)
        if i < N - M:
            t = (d * (t - ord(txt[i]) * h) + ord(txt[i + M])) % q

            if t < 0:
                t += q

def main():
    text_file_path = input("Enter the file path for the text: ")

    try:
        with open(text_file_path, 'r') as text_file:
            txt, pat = text_file.read().splitlines()
    except FileNotFoundError:
        print("Error opening file!")
        return
    except ValueError:
        print("Error reading text and pattern from file!")
        return

    q = 101
    search(pat, txt, q)

if __name__ == "__main__":
    main()
