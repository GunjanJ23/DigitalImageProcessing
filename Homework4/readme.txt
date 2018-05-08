NAME: Gunjan Jhawar
USC ID: 1857-5342-64
E-mail: gunjanjh@usc.edu

The following steps will guide you to execute the files that are contained in HW4.zip folder.

Steps to run the program:

1. Unzip the folder on your system.
2. Open terminal. Do cd <address of the folder>.
3. For Question1:

   -In terminal put: python lenet5.py
   -You will get accuracy for training
   -You will get loss and accuracy graph. Save them and cancel it. After canceling it, it will run for test 
    data.
   -Now, you will get test accuracy along with classification accuracy using SVM and RF classifier and their
    corresponding confusion matrix.
4. For Question2:
   -In terminal put: python mnist.py
   -You will get accuracy for training
   -You will get accuracy for testing
   -Following parameters can be changed:
    Data change validation_size: mnist = read_data_sets(args.data_dir, reshape=False, validation_size=20000)
    Components after PCA change dim: reduced_feat_train, pca = reduce_feat_dim(selected_feat_train, dim=64)
	