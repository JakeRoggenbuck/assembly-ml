from distutils.core import setup, Extension

def main():
    setup(name="add_one",
          version="1.0.0",
          description="Python interface for adding 1 as a function",
          author="<your name>",
          author_email="your_email@gmail.com",
          ext_modules=[Extension("add_one", ["main.c"])])

if __name__ == "__main__":
    main()
