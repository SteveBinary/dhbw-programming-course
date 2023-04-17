import papermill as pm


TRAINING_TEST_SPLITS = [(0.5, '50-50'), (0.3, '70-30'), (0.1, '90-10')]
ACTIVATION_FUNCTIONS = ['tanh', 'sigmoid', 'relu']
TRAINING_EPOCHS = 5
NUMBER_OF_TRAINING_SESSIONS = 50


for training_session in range(10, NUMBER_OF_TRAINING_SESSIONS):
    for activation_function in ACTIVATION_FUNCTIONS:
        for training_test_split in TRAINING_TEST_SPLITS:
            print()
            print(f"Running:")
            print(f"\tsplit    : {training_test_split[1]}")
            print(f"\tfunction : {activation_function}")
            print(f"\tsession  : {training_session + 1}")
            print()

            pm.execute_notebook(
                input_path="group4-gtsrb.ipynb",
                output_path="group4-gtsrb.output.ipynb",
                parameters={
                    "TRAINING_TEST_SPLIT": training_test_split[0],
                    "TRAINING_TEST_SPLIT_NAME": training_test_split[1],
                    "ACTIVATION_FUNCTION": activation_function,
                    "TRAINING_SESSION": training_session + 1,
                    "TRAINING_EPOCHS": TRAINING_EPOCHS
                }
            )
