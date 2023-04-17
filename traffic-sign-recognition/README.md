# [Group 4] German Traffic Sign Recognition

- original dataset: [https://benchmark.ini.rub.de/gtsrb_dataset.html](https://benchmark.ini.rub.de/gtsrb_dataset.html)
- improved dataset and Jupyter code: [https://www.kaggle.com/code/shivank856/gtsrb-cnn-98-test-accuracy](https://www.kaggle.com/code/shivank856/gtsrb-cnn-98-test-accuracy)

## Aufgabe

Anhand eines Datensatzes mit deutschen Verkehrsschildern untersuchen, wie sich folgende Trainingskonfiguration auf die test accuracy auswirken:
- Training-Test-Split (90-10, 70-30, 50-50)
- jeweils die Aktivierungsfunktionen relu, sigmoid, tanh (letzter Layer ist immer softmax)
- jede Trainingskonfiguration 10 Mal ausführen (jeweils 5 Epochen) und den Durchschnitt bilden


## Installation (WSL2, Ubuntu 22.04)

Following [this tutorial](https://www.tensorflow.org/install/pip#windows-wsl2):

1. [Install Miniconda](https://docs.conda.io/projects/conda/en/latest/user-guide/install/linux.html)
2. Install `gcc`:
    ```shell
    sudo apt install gcc    
    ```
3. [Install NVIDIA CUDA toolkit 11.2](https://developer.nvidia.com/cuda-11.2.2-download-archive?target_os=Linux&target_arch=x86_64&target_distro=WSLUbuntu&target_version=20&target_type=runfilelocal)
4. [Download NVIDIA cuDNN 8.1](https://developer.nvidia.com/compute/machine-learning/cudnn/secure/8.1.1.33/11.2_20210301/Ubuntu20_04-x64/libcudnn8_8.1.1.33-1+cuda11.2_amd64.deb) and [Install](https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html#installlinux-deb), and:
    ```shell
    sudo apt-get install libcudnn8=8.1.1.33-1+cuda11.2
    ```
5. Create a conda environment:
    ```shell
    conda create --name tf python=3.9
    ```
    **The environment _tf_ has to be activated for the rest of the installation!**
    ```shell
    conda activate tf
    ```
6. Run:
    ```shell
    conda install -c conda-forge cudatoolkit=11.2 cudnn=8.1
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CONDA_PREFIX/lib/
    mkdir -p $CONDA_PREFIX/etc/conda/activate.d
    echo 'export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CONDA_PREFIX/lib/' > $CONDA_PREFIX/etc/conda/activate.d/env_vars.sh
    ```
7. Install Tensorflow:
    ```shell
    pip install --upgrade pip
    pip install tensorflow
    ```
8. Verify the installation:
    - CPU:
        ```shell
        python3 -c "import tensorflow as tf; print(tf.reduce_sum(tf.random.normal([1000, 1000])))"
        ```
    - GPU:
        ```shell
        python3 -c "import tensorflow as tf; print(tf.config.list_physical_devices('GPU'))"
        ```
        The output should contain this:
        ```
        [PhysicalDevice(name='/physical_device:GPU:0', device_type='GPU')]
        ```
9. Install necessary packages for Jupyter Notebook:\
    Installing the `Python` and `Jupyter` extensions in VS Code is recommended. Make sure these are also installed in WSL2!
    ```shell
    conda install -c anaconda ipykernel
    python -m ipykernel install --user --name=tf
    pip install matplotlib
    ```
10. Select the correct Kernel in VS Code (e.g. `tf(Python 3.9.16)`)
