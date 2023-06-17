#include <bits/stdc++.h>
using namespace std;

#define MAX_FRAMES 10

int optimalPageReplacement(int pages[], int n, int frames[], int frameSize)
{
  int pageFaults = 0;

  for (int i = 0; i < n; i++)
  {
    bool pageExists = false;

    for (int j = 0; j < frameSize; j++)
    {
      if (frames[j] == pages[i])
      {
        pageExists = true;
        break;
      }
    }

    if (!pageExists)
    {
      int position = -1, farthest = i + 1;

      for (int j = 0; j < frameSize; j++)
      {
        int k;
        for (k = i + 1; k < n; k++)
        {
          if (frames[j] == pages[k])
          {
            if (k > farthest)
            {
              farthest = k;
              position = j;
            }
            break;
          }
        }
        if (k == n)
        {
          position = j;
          break;
        }
      }

      if (position == -1)
        position = 0;

      frames[position] = pages[i];
      pageFaults++;
    }
  }

  return pageFaults;
}

int main()
{
  int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
  int n = sizeof(pages) / sizeof(pages[0]);

  int frames[MAX_FRAMES];
  int frameSize = 3;

  for (int i = 0; i < frameSize; i++)
  {
    frames[i] = -1; // Initialize frames as empty
  }

  int pageFaults = optimalPageReplacement(pages, n, frames, frameSize);

  printf("Total Page Faults: %d\n", pageFaults);

  return 0;
}
