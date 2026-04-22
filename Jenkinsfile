pipeline {
  agent {
    label 'docker-agent-c'
  }

  triggers {
    pollSCM('H/5 * * * *')
  }

  stages {

    stage('Checkout') {
      steps {
        checkout scm
      }
    }

    stage('Build') {
      steps {
        sh 'gcc main.c -o main'
      }
    }

    stage('Test') {
      steps {
        sh './main'
      }
    }

    stage('Test Docker') {
      steps {
        sh 'docker ps'
      }
    }

    stage('Docker Build') {
      steps {
        sh '''
          docker build -t robinparker995/employee_payroll_system:${BUILD_NUMBER} .
        '''
      }
    }

    stage('Push Image') {
      steps {
        withCredentials([usernamePassword(
          credentialsId: 'dockerhub-creds',
          usernameVariable: 'DOCKER_USER',
          passwordVariable: 'DOCKER_PASS'
        )]) {
          sh '''
            echo "$DOCKER_PASS" | docker login -u "$DOCKER_USER" --password-stdin

            docker push robinparker995/employee_payroll_system:${BUILD_NUMBER}
          '''
        }
      }
    }

    stage('Deploy') {
      steps {
        sh '''
          docker stop myapp || true
          docker rm myapp || true

          docker run -d \
            --name myapp \
            robinparker995/employee_payroll_system:${BUILD_NUMBER}
        '''
      }
    }

    stage('Deliver') {
      steps {
        sh '''
          mkdir -p output/
          cp main output/
        '''
        archiveArtifacts artifacts: 'output/main', fingerprint: true
      }
    }
  }

  post {
    success {
      echo 'Pipeline completed successfully!'
    }
    failure {
      echo 'Pipeline failed'
    }
    always {
      cleanWs()
    }
  }
}